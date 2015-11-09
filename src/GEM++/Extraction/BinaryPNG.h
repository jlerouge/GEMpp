#ifndef GEMPP_BINARYPNG_H
#define GEMPP_BINARYPNG_H

#include <QImage>
#include <QFileInfo>
#include "../Core/Printer.h"
#include "qgarlib/GenImage.h"

using namespace qgar;

/**
 * @brief The BinaryPNG class is a utility that provides methods
 * to manipulate monochrome (black and white) PNG images.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT BinaryPNG {
    public:
        /**
         * @brief Reads a monochrome PNG image.
         * @param filename the path to the image file to read
         * @param borderWidth the width of the border to add to the image after reading
         * @param color the color of the border to add to the image after reading
         * @return the monochrome image with an additional border
         */
        static BinaryImage read(QString filename, uint borderWidth = 0, QGEbw color = QGE_BW_WHITE);

        /**
         * @brief Writes a monochrome PNG image.
         * @param filename the path to the image file to write
         * @param borderWidth the width of the border to add to the image before writing
         * @param color the color of the border to add to the image before writing
         */
        static void write(BinaryImage &img, QString filename, uint borderWidth = 0, QGEbw color = QGE_BW_WHITE);

        /**
         * @brief Adds a rectangular border to a monochrome image, with a fixed width.
         * @param img the monochrome image
         * @param borderWidth the width of the border to add to the image
         * @param color the color of the border to add to the image
         */
        static BinaryImage addBorder(BinaryImage &img, uint borderWidth, QGEbw color);
};

#endif /*BINARYPNG_H*/
