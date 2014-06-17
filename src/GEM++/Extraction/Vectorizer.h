#ifndef __VECTORIZER_H__
#define __VECTORIZER_H__

#include <cstdlib>
#include <iostream>
#include <list>
#include <QPoint>
#include "Extractor.h"
#include "BinaryPNG.h"
#include "qgarlib/CleanedBinaryImage.h"
#include "qgarlib/Dist34BlackCCImage.h"
#include "qgarlib/DxfFile.h"
#include "qgarlib/SvgFile.h"
#include "qgarlib/LabeledSkeletonImage.h"
#include "qgarlib/LinkedChainList.h"
#include "qgarlib/RWSegmentVector.h"

using namespace qgar;

class DLL_EXPORT Vectorizer : public Extractor {
    public:
        Vectorizer();
        Vectorizer(const QString &input, const QString &output, ExtractionConfiguration *excfg);
        ~Vectorizer();

        void setBackground(const QString &filename);
        QString getBackground();

    private:
        QString background_;
        void performExtraction();

};

#endif /*__VECTORIZER_H__*/
