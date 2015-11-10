#include "Zernike.h"

QList<double> zernike2D (const BinaryImage &im, int L, double rad) {
    QList<double> zvalues;
    int N;

    // N is the minimum of im.width() and im.height()
    N = im.width() < im.height() ? im.width() : im.height();
    if (L >= GEMPP_MAX_ORDER)
        Exception(QString("Zernike polynomial order (=%1) must be less than %2").arg(L).arg(GEMPP_MAX_ORDER-1));
    if (rad <= 0.0)
        rad = N;

    static double H1[GEMPP_MAX_ORDER][GEMPP_MAX_ORDER];
    static double H2[GEMPP_MAX_ORDER][GEMPP_MAX_ORDER];
    static double H3[GEMPP_MAX_ORDER][GEMPP_MAX_ORDER];
    static char init=1;

    double COST[GEMPP_MAX_ORDER], SINT[GEMPP_MAX_ORDER], R[GEMPP_MAX_ORDER];
    double Rn, Rnm, Rnm2, Rnnm2, Rnmp2, Rnmp4;

    double a,b,x, y, r, r2, f, const_t; // area
    int n,m,i,j;

    double AR[GEMPP_MAX_ORDER][GEMPP_MAX_ORDER], AI[GEMPP_MAX_ORDER][GEMPP_MAX_ORDER];

    double sum = 0;
    int cols = im.width();
    int rows = im.height();

    // compute x/0, y/0 and 0/0 moments to center the unit circle on the centroid
    double moment10 = 0.0, moment00 = 0.0, moment01 = 0.0;
    double intensity;
    for (i = 0; i < cols; i++)
        for (j = 0; j < rows; j++) {
            intensity = (int)(im.pixel(i, j) == QGE_BW_WHITE);
            sum += intensity;
            moment10 += (i+1) * intensity;
            moment00 += intensity;
            moment01 += (j+1) * intensity;
        }
    double m10_m00 = moment10/moment00;
    double m01_m00 = moment01/moment00;


    // Pre-initialization of statics
    if (init) {
        for (n = 0; n < GEMPP_MAX_ORDER; n++) {
            for (m = 0; m <= n; m++) {
                if (n != m) {
                    H3[n][m] = -(double)(4.0 * (m+2.0) * (m + 1.0) ) / (double)( (n+m+2.0) * (n - m) ) ;
                    H2[n][m] = ( (double)(H3[n][m] * (n+m+4.0)*(n-m-2.0)) / (double)(4.0 * (m+3.0)) ) + (m+2.0);
                    H1[n][m] = ( (double)((m+4.0)*(m+3.0))/2.0) - ( (m+4.0)*H2[n][m] ) + ( (double)(H3[n][m]*(n+m+6.0)*(n-m-4.0)) / 8.0 );
                }
            }
        }
        init = 0;
    }

    // Zero-out the Zernike moment accumulators
    for (n = 0; n <= L; n++) {
        for (m = 0; m <= n; m++) {
            AR[n][m] = AI[n][m] = 0.0;
        }
    }

    for (i = 0; i < cols; i++) {
        x = (i+1 - m10_m00) / rad;
        for (j = 0; j < rows; j++) {
            y = (j+1 - m01_m00) / rad;
            r2 = x*x + y*y;
            r = sqrt (r2);
            if ( r < DBL_EPSILON || r > 1.0) continue;
            /*compute all powers of r and save in a table */
            R[0] = 1;
            for (n=1; n <= L; n++) R[n] = r*R[n-1];
            /* compute COST SINT and save in tables */
            a = COST[0] = x/r;
            b = SINT[0] = y/r;
            for (m = 1; m <= L; m++) {
                COST[m] = a * COST[m-1] - b * SINT[m-1];
                SINT[m] = a * SINT[m-1] + b * COST[m-1];
            }

        // compute contribution to Zernike moments for all
        // orders and repetitions by the pixel at (i,j)
        // In the paper, the intensity was the raw image intensity
            f = (int)(im.pixel(i, j) == QGE_BW_WHITE) / sum;

            Rnmp2 = Rnm2 = 0;
            for (n = 0; n <= L; n++) {
                const_t = (n+1) * f/GEMPP_PI;
                Rn = R[n];
                if (n >= 2) Rnm2 = R[n-2];
                for (m = n; m >= 0; m -= 2) {
                    if (m == n) {
                        Rnm = Rn;
                        Rnmp4 = Rn;
                    } else if (m == n-2) {
                        Rnnm2 = n*Rn - (n-1)*Rnm2;
                        Rnm = Rnnm2;
                        Rnmp2 = Rnnm2;
                    } else {
                        Rnm = H1[n][m] * Rnmp4 + ( H2[n][m] + (H3[n][m]/r2) ) * Rnmp2;
                        Rnmp4 = Rnmp2;
                        Rnmp2 = Rnm;
                    }
                    AR[n][m] += const_t * Rnm * COST[m];
                    AI[n][m] -= const_t * Rnm * SINT[m];
                }
            }
        }
    }

    for (n = 0; n <= L; n++) {
        for (m = 0; m <= n; m++) {
            if ( (n-m) % 2 == 0 ) {
                AR[n][m] *= AR[n][m];
                AI[n][m] *= AI[n][m];
                zvalues.push_back(fabs (sqrt ( AR[n][m] + AI[n][m] )));
            }
        }
    }
    return zvalues;
}
