#ifndef GEMPP_VECTORIZER_H
#define GEMPP_VECTORIZER_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <QPoint>
#include "SingleExtractor.h"
#include "BinaryPNG.h"
#include "qgarlib/CleanedBinaryImage.h"
#include "qgarlib/Dist34BlackCCImage.h"
#include "qgarlib/DxfFile.h"
#include "qgarlib/SvgFile.h"
#include "qgarlib/LabeledSkeletonImage.h"
#include "qgarlib/LinkedChainList.h"
#include "qgarlib/RWSegmentVector.h"

using namespace qgar;

/**
 * @brief The Vectorizer class allows the vectorization of binary images, using the skeletonization
 * of the distance transform. The result is exported as an SVG file (eventually referencing a raster
 * image representing the background, which will not be vectorized).
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT Vectorizer : public SingleExtractor {
    public:
        /**
         * @brief Constructs a new Vectorizer object.
         */
        Vectorizer();

        /**
         * @brief Constructs a Vectorizer object with parameters.
         * @param input the input filename of the extraction
         * @param output the output filename of the extraction
         * @param metadata the metadata filename on the extraction
         * @param excfg configuration of the extractor
         */
        Vectorizer(const QString &input, const QString &output, ExtractionConfiguration *excfg);

        /**
         * @brief Destructs a Vectorizer object.
         */
        ~Vectorizer();

        /**
         * @brief Sets the filename of the background image.
         * @param filename the background filename
         */
        void setBackground(const QString &filename);

        /**
         * @brief Returns the filename of the background image.
         * @return the background filename
         */
        QString getBackground();

    private:
        /**
         * @brief The filename of the background image.
         */
        QString background_;

        void performExtraction();
};

#endif /* GEMPP_VECTORIZER_H */
