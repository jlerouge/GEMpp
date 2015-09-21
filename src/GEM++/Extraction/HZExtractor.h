#ifndef __HZEXTRACTOR_H__
#define __HZEXTRACTOR_H__

#include <QRectF>
#include <QList>
#include <QImage>
#include <QColor>
#include "SingleExtractor.h"
#include "../Model/Graph.h"

class DLL_EXPORT HomogeneousZoneExtractor : virtual public SingleExtractor {
    public:
        HomogeneousZoneExtractor();
        HomogeneousZoneExtractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg);
        virtual ~HomogeneousZoneExtractor();

        QColor color(QRect rect);

        static QSet<int> visibility(QList<QRectF> rectangles, QRectF rect, double thresh);
        static QSet<int> inclusion(QList<QRectF> rectangles, QRectF rect, double thresh = 1.0);

    protected:
        Graph *graph_;
        QImage *img_;
        void performExtraction();

    //private:
        //static QSet<int> directionalVisibility(QList<QRectF> rects, QList<int> visibleRects, QRectF rect, double thresh);
};

#endif /*__HZEXTRACTOR_H__*/
