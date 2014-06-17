#include "BinaryPNG.h"

BinaryImage BinaryPNG::read(QString filename, uint borderWidth, QGEbw color) {
    if(!filename.endsWith(".png", Qt::CaseInsensitive))
        GEM_exception(QString("The given input (%1) is not a *.png image.").arg(filename));
    if(!QFileInfo(filename).exists())
        GEM_exception(QString("The given input (%1) does not exist.").arg(filename));
    QImage source = QImage(filename);
    if(source.format() != QImage::Format_Mono)
        GEM_exception(QString("The given input (%1) is not a monochrome image.").arg(filename));

    BinaryImage img = BinaryImage(source.width(), source.height());
    QVector<QRgb> table = source.colorTable();
    QVector<QGEbw> transl;
    if(qGray(table[0]) == 0) {
        transl.push_back(QGE_BW_BLACK);
        transl.push_back(QGE_BW_WHITE);
    } else {
        transl.push_back(QGE_BW_WHITE);
        transl.push_back(QGE_BW_BLACK);
    }
    for(int x=0; x < source.width(); ++x)
        for(int y=0; y < source.height(); ++y)
            img.setPixel(x, y, transl[source.pixelIndex(x,y)]);
    return addBorder(img, borderWidth, color);
}

void BinaryPNG::write(BinaryImage &img, QString filename, uint borderWidth, QGEbw color) {
    if(!filename.endsWith(".png", Qt::CaseInsensitive))
        GEM_exception(QString("The given output (%1) is not a *.png image.").arg(filename));
    BinaryImage imgCopy = addBorder(img, borderWidth, color);
    QImage result = QImage(imgCopy.width(), imgCopy.height(), QImage::Format_Mono);
    for(int x=0; x < imgCopy.width(); ++x)
        for(int y=0; y < imgCopy.height(); ++y)
            result.setPixel(x, y, 1-imgCopy.pixel(x,y));
    result.save(filename);
}

BinaryImage BinaryPNG::addBorder(BinaryImage &img, uint borderWidth, QGEbw color) {
    if(borderWidth == 0)
        return img;
    BinaryImage result = BinaryImage(img.width()+2*borderWidth, img.height()+2*borderWidth);
    memset(result.pPixMap(), color, sizeof(BinaryImage::value_type) * result.width() * result.height());
    for(int x=0; x < img.width(); ++x)
        for(int y=0; y < img.height(); ++y)
            result.setPixel(x+borderWidth, y+borderWidth, img.pixel(x,y));
    return result;
}
