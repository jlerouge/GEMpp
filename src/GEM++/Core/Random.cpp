#include "Random.h"

void Random::seedRand(int seed) {
    if(seed < 0)
        qsrand(time(NULL) + GETPID() * 1000);
    else
        qsrand(seed);
    rand(); // The first value is not so random...
}

double Random::randDouble() {
    return (double)qrand()/(double)RAND_MAX;
}

double Random::randDouble(double low, double high) {
    return randDouble()*(high - low) + low;
}

int Random::randInt(int low, int high) {
    return low + (int) ((high + 1 - low)*(qrand()/(RAND_MAX + (double)low)));
}

void Random::randPerm(QVector<int> &v) {
    int temp, r, n = v.size();

    // Permutation
    for(int i=0; i<n; ++i) {
        r = randInt(0, n-1);
        temp = v[i];
        v[i] = v[r];
        v[r] = temp;
    }
}

QVector<int> Random::randPerm(int n) {
    return randPerm(1,n);
}

QVector<int> Random::randPerm(int low, int high) {
    QVector<int> res = id(low, high);
    randPerm(res);
    return res;
}

QVector<int> Random::id(int n) {
    return id(1,n);
}

QVector<int> Random::id(int low, int high) {
    QVector<int> res = QVector<int>(high-low+1);
    for(int i=0; i<(high-low+1); ++i)
        res[i] = low+i;
    return res;
}
