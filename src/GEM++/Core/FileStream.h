#ifndef GEMPP_FILESTREAM_H
#define GEMPP_FILESTREAM_H

#include <QFile>
#include "IPrintable.h"

/**
 * @brief The FileStream class is a utility that provides methods
 * to load, save and remove files.
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT FileStream {
    public:
        /**
         * @brief Constructs a new FileStream utility.
         */
        FileStream();
        /**
         * @brief Destructs a FileStream utility.
         */
        ~FileStream();

        /**
         * @brief Loads a file and returns its content.
         * @param filename the path to the file
         * @return the content of the file
         */
        static QString loadFile(const QString &filename);

        /**
         * @brief Serializes an IPrintable to a file.
         * @param ip the IPrintable object to serialize
         * @param filename the path to the file
         */
        static void saveFile(IPrintable *ip, const QString &filename);

        /**
         * @brief Serializes a QString to a file.
         * @param s the QString to serialize
         * @param filename the path to the file
         */
        static void saveFile(const QString &s, const QString &filename);

        /**
         * @brief Removes a file.
         * @param filename the path to the file
         * @return true if successful, false otherwise
         */
        static bool removeFile(const QString &filename);
};

#endif /*FILESTREAM_H*/
