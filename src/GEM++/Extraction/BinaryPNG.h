#ifndef __BINARYPNG_H__
#define __BINARYPNG_H__

#include <QImage>
#include <QFileInfo>
#include "../Core/Printer.h"
#include "qgarlib/GenImage.h"

using namespace qgar;

class DLL_EXPORT BinaryPNG {
    public:
        static BinaryImage read(QString filename, uint borderWidth = 0, QGEbw color = QGE_BW_WHITE);
        static void write(BinaryImage &img, QString filename, uint borderWidth = 0, QGEbw color = QGE_BW_WHITE);
        static BinaryImage addBorder(BinaryImage &img, uint borderWidth, QGEbw color);
};

#endif /*__BINARYPNG_H__*/
