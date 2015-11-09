#ifndef GEMPP_HZEXTRACTOR_H
#define GEMPP_HZEXTRACTOR_H

#include <QRectF>
#include <QList>
#include <QImage>
#include <QColor>
#include "SingleExtractor.h"
#include "Model/Graph.h"

/**
 * @brief The HomogeneousZoneExtractor class allows the extraction of homogeneous colored zones on documents.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT HomogeneousZoneExtractor : virtual public SingleExtractor {
    public:
        /**
         * @brief Constructs a new HomogeneousZoneExtractor object.
         */
        HomogeneousZoneExtractor();

        /**
         * @brief Constructs a HomogeneousZoneExtractor object with parameters.
         * @param input the input of the extraction
         * @param output the output of the extraction
         * @param metadata metadata on the extraction
         * @param excfg configuration of the extractor
         */
        HomogeneousZoneExtractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg);

        /**
         * @brief Destructs a HomogeneousZoneExtractor object.
         */
        virtual ~HomogeneousZoneExtractor();

        /**
         * @brief Returns the mean color in a rectangular zone.
         * @param rect the rectangular zone
         */
        QColor color(QRect rect);

        /**
         * @brief Returns the indices of the rectangles that are visible from a particular rectangle.
         * The visibility relationship is controlled by a threshold, which operates on the visibility rate,
         * which is computed by dividing the length of the intersection of the mutually visible segments by
         * the length of the shortest segment.
         * @param rectangles the list of rectangle to test
         * @param rect the current rectangle
         * @param thresh the visibility threshold, between 0 and 1
         */
        static QSet<int> visibility(QList<QRectF> rectangles, QRectF rect, double thresh);

        /**
         * @brief Returns the indices of the rectangles that intersects a particular rectangle.
         * The intersection relationship is controlled by a threshold, which operates on the intersection rate,
         * which is computed by dividing the area of the intersection by the area of the intersecting rectangle.
         * When this threshold equals 1, this method tests the complete inclusion of the rectangle in the others.
         * @param rectangles the list of rectangle to test
         * @param rect the current rectangle
         * @param thresh the intersection threshold, between 0 and 1
         */
        static QSet<int> intersection(QList<QRectF> rectangles, QRectF rect, double thresh = 1.0);

    protected:
        /**
         * @brief The output graph.
         */
        Graph *graph_;

        /**
         * @brief The input image.
         */
        QImage *img_;

        /**
         * @brief The input image.
         */

        void performExtraction();

    //private:
        //static QSet<int> directionalVisibility(QList<QRectF> rects, QList<int> visibleRects, QRectF rect, double thresh);
};

#endif /*HZEXTRACTOR_H*/
