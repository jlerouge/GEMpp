#ifndef PIVAJ_UTILITY_H
#define PIVAJ_UTILITY_H

#include <QMetaType>
#include <opencv2/core.hpp>
#include <BRAID/dataStructures/images/Image.hpp>
#include <QRect>
#include <QImage>
#include <QSize>
#include <QColor>
#include "Constants.h"
#include "Exception.h"

namespace PIVAJ {
    class DLL_EXPORT Utility {
        public:
            static cv::Size toCvSize(const QSize &s);
            static QSize toQSize(const cv::Size &s);
            static cv::Rect toCvRect(const QRect &r);
            static QRect toQRect(const cv::Rect &r);
            static cv::Point toCvPoint(const QPoint &p);
            static QPoint toQPoint(const cv::Point &p);
            static QImage toQImage(Image *image);
            static QSize size(Image *image);
            static QSize size(cv::Mat mat);
            static cv::Scalar toCvScalar(const QColor &c, int channels);
            static QColor toQColor(const cv::Scalar &c);

            static QString toString(const QPointF &point);
            static QPointF toPoint(const QString &string);
            static QString toString(const QSizeF &size);
            static QSizeF toSize(const QString &string);
            static QString toString(const QRectF &rect);
            static QRectF toRect(const QString &string);

            static QString toString(const QVariant &value, QMetaType::Type type);
            static QVariant fromString(const QString &string, QMetaType::Type type);
    };
    QTextStream &operator <<(QTextStream &stream, const QRectF &rect);
    QTextStream &operator <<(QTextStream &stream, const QSizeF &size);
    QTextStream &operator <<(QTextStream &stream, const QRect &rect);
    QTextStream &operator <<(QTextStream &stream, const QSize &size);
}

#endif /* PIVAJ_UTILITY_H */
