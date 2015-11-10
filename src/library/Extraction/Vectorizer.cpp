#include "Vectorizer.h"

Vectorizer::Vectorizer() : SingleExtractor() {
    background_ = "";
}

Vectorizer::Vectorizer(const QString &input, const QString &output, ExtractionConfiguration *excfg) : SingleExtractor(input, output, "", excfg) {
    background_ = "";
}

Vectorizer::~Vectorizer() {}

void Vectorizer::setBackground(const QString &filename) {
    background_ = filename;
}

QString Vectorizer::getBackground() {
    return background_;
}

void Vectorizer::performExtraction() {
    if(excfg_->verbose)
        cout << "Loading source image..." << endl;
    BinaryImage sourceImg = BinaryPNG::read(input_.toString());

    if(excfg_->verbose)
        cout << "Cleaning source image..." << endl;
    CleanedBinaryImage cleanedImg(sourceImg);

    if(excfg_->verbose)
        cout << "Computing distance transform of source image..." << endl;
    Dist34BlackCCImage dist34Img(cleanedImg);

    if(excfg_->verbose)
        cout << "Performing skeletonization..." << endl;
    LabeledSkeletonImage skelImg(dist34Img, excfg_->pruningSize+20);

    if(excfg_->verbose)
        cout << "Chaining skeleton points..." << endl;
    LinkedChainList chainsList(skelImg);

    if(excfg_->verbose)
        cout << "Performing polygonal approximation..." << endl;
    LinkedChainList::iterator itChain = chainsList.begin();

    //DxfFile segResFile(output_.toStdString().c_str());
    SvgFile segResFile(output_.toString().toStdString().c_str());
    segResFile.openWONLY();
    segResFile.writeHeader(sourceImg.width(), sourceImg.height());
    if(!background_.isEmpty())
        segResFile.writeBackground(background_.toStdString().c_str(), sourceImg.width(), sourceImg.height());

    while (itChain != chainsList.end()) {
        // Polygonal approximation
        RWSegmentVector* aPolygApprox = new RWSegmentVector(*itChain);
        RWSegmentVector::iterator itSeg = aPolygApprox->begin();

        // Access the beginning of the list of points
        list<Point>::iterator itPoint = (itChain->pointList()).begin();

        // Compute line width
        int myw = (int) skelImg.pixel(itPoint->x(), itPoint->y());
        int numPixel = 1;
        long int totalWidth;
        int totalNumPixels;

        while ((*itPoint) != itSeg->target()) {
            ++itPoint;
            myw += (int) skelImg.pixel(itPoint->x(), itPoint->y());
            ++numPixel;
        }

        myw = (myw * 2) / (3 * numPixel);
        totalWidth = myw * numPixel;
        totalNumPixels = numPixel;

        // Build a Qgar polyline - Initialize width (useless!)
        QgarSegment tmpSeg(itSeg->source(), itSeg->target(), myw, QGE_COLOR_DEFAULT);
        QgarPolyline* myPol = new QgarPolyline(tmpSeg);
        ++itSeg;

        // Complete it with the remaining segments
        while (itSeg != aPolygApprox->end()) {
            // Compute line width
            myw = (int) skelImg.pixel(itPoint->x(), itPoint->y());
            numPixel = 1;
            while ((*itPoint) != itSeg->target()) {
                ++itPoint;
                myw += (int) skelImg.pixel(itPoint->x(), itPoint->y());
                ++numPixel;
            }

            myw = (myw * 2) / (3 * numPixel);
            totalWidth += myw * numPixel;
            totalNumPixels += numPixel;

            // Expand the polyline
            myPol->appendTarget(itSeg->target());
            ++itSeg;
        }

        // Set the final width, and save the Qgar polyline
        myPol->setThickness(totalWidth/totalNumPixels);
        segResFile.write(*myPol); //, totalWidth, QGE_COLOR_BLACK, QGE_OUTLINE_SOLID);
        delete myPol;
        delete aPolygApprox;
        ++itChain;
    }

    // CLOSE FILES
    segResFile.writeFooter();
    segResFile.close();
    if(excfg_->verbose)
        cout << "Vectorization done." << endl;
}
