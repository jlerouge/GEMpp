#include "Utility.h"

cv::Size PIVAJ::Utility::toCvSize(const QSize &r) {
    return cv::Size(r.width(), r.height());
}

QSize PIVAJ::Utility::toQSize(const cv::Size &r) {
    return QSize(r.width, r.height);
}

cv::Rect PIVAJ::Utility::toCvRect(const QRect &r) {
    return cv::Rect(r.x(), r.y(), r.width(), r.height());
}

QRect PIVAJ::Utility::toQRect(const cv::Rect &r) {
    return QRect(r.x, r.y, r.width, r.height);
}

cv::Point PIVAJ::Utility::toCvPoint(const QPoint &p) {
    return cv::Point(p.x(), p.y());
}

QPoint PIVAJ::Utility::toQPoint(const cv::Point &p) {
    return QPoint(p.x, p.y);
}

QImage PIVAJ::Utility::toQImage(Image *image) {
    QImage result(image->getWidth(), image->getHeight(), QImage::Format_RGB32);

    for(int y=0; y < image->getHeight(); ++y)
        for(int x=0; x < image->getWidth(); ++x)
            result.setPixel(x, y, qRgb(image->getPixel(y, x, 2), image->getPixel(y, x, 1), image->getPixel(y, x, 0)));
    return result;
}

QSize PIVAJ::Utility::size(Image *image) {
    return size(*image);
}

QSize PIVAJ::Utility::size(cv::Mat mat) {
    return QSize(mat.cols, mat.rows);
}

cv::Scalar PIVAJ::Utility::toCvScalar(const QColor &c, int channels) {
    if(channels == 3)
        return cv::Scalar(c.blue(), c.green(), c.red());
    return cv::Scalar(c.lightness());
}

QColor PIVAJ::Utility::toQColor(const cv::Scalar &c) {
    if(c.channels == 3)
        return QColor(c[2], c[1], c[0]);
    return QColor(c[0], c[0], c[0]);
}

QString PIVAJ::Utility::toString(const QPointF &point) {
    return QString("%1,%2").arg(point.x()).arg(point.y());
}

QPointF PIVAJ::Utility::toPoint(const QString &string) {
    QStringList sl = string.split(",");
    return QPointF(sl[0].toFloat(), sl[1].toFloat());
}

QString PIVAJ::Utility::toString(const QSizeF &size) {
    return QString("%1,%2").arg(size.width()).arg(size.height());
}

QSizeF PIVAJ::Utility::toSize(const QString &string) {
    QStringList sl = string.split(",");
    return QSizeF(sl[0].toFloat(), sl[1].toFloat());
}

QString PIVAJ::Utility::toString(const QRectF &rect) {
    return QString("%1,%2 %3,%4").arg(rect.left()).arg(rect.top()).arg(rect.right()).arg(rect.bottom());
}

QRectF PIVAJ::Utility::toRect(const QString &string) {
    QStringList points = string.split(" "), sl;
    QPointF p1, p2;
    sl = points[0].split(",");
    p1 = QPointF(sl[0].toFloat(), sl[1].toFloat());
    sl = points[1].split(",");
    p2 = QPointF(sl[0].toFloat(), sl[1].toFloat());
    return QRectF(p1, p2);
}

QString PIVAJ::Utility::toString(const QVariant &value, QMetaType::Type type) {
    switch(type) {
        case QMetaType::Bool:
            return value.toBool()? "true" : "false";
        case QMetaType::UInt:
            return QString::number(value.toUInt());
        case QMetaType::Int:
            return QString::number(value.toInt());
        case QMetaType::Float:
            return QString::number(value.toFloat());
        case QMetaType::Double:
            return QString::number(value.toDouble());
        case QMetaType::QRect:
            return toString(value.toRect());
        case QMetaType::QRectF:
            return toString(value.toRectF());
        case QMetaType::QSize:
            return toString(value.toSize());
        case QMetaType::QSizeF:
            return toString(value.toSizeF());
        case QMetaType::QString:
            return value.toString();
        default:
            Exception("PIVAJ::Utility::toString is not implemented for QMetaType::Type" + QString::number(type));
            break;
    }
    return QString();
}

QVariant PIVAJ::Utility::fromString(const QString &string, QMetaType::Type type) {
    switch(type) {
        case QMetaType::Bool:
            return (string.compare("true", Qt::CaseInsensitive) == 0);
        case QMetaType::UInt:
            return string.toUInt();
        case QMetaType::Int:
            return string.toInt();
        case QMetaType::Float:
            return string.toFloat();
        case QMetaType::Double:
            return string.toDouble();
        case QMetaType::QRect:
            return toRect(string).toRect();
        case QMetaType::QRectF:
            return toRect(string);
        case QMetaType::QSize:
            return toSize(string).toSize();
        case QMetaType::QSizeF:
            return toSize(string);
        case QMetaType::QString:
            return string;
        default:
            Exception("PIVAJ::Utility::fromString is not implemented for QMetaType::Type" + QString::number(type));
            break;
    }
    return QVariant();
}

QTextStream &PIVAJ::operator <<(QTextStream &stream, const QRectF &rect) {
    stream << "tl:" << rect.left() << "," << rect.top() << " br:" << rect.right() << "," << rect.bottom() << " " << rect.size();
    return stream;
}

QTextStream &PIVAJ::operator <<(QTextStream &stream, const QSizeF &size) {
    stream << "sz:" << size.width() << "," << size.height();
    return stream;
}

QTextStream &PIVAJ::operator <<(QTextStream &stream, const QRect &rect) {
    stream << "tl:" << rect.left() << "," << rect.top() << " br:" << rect.right() << "," << rect.bottom() << " " << rect.size();
    return stream;
}

QTextStream &PIVAJ::operator <<(QTextStream &stream, const QSize &size) {
    stream << "sz:" << size.width() << "," << size.height();
    return stream;
}

