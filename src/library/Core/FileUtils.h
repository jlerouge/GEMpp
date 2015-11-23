#ifndef GEMPP_FILEUTILS_H
#define GEMPP_FILEUTILS_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include "Exception.h"
#include "IPrintable.h"

/**
 * @brief The FileUtils class is a utility that provides methods to load, save and remove files.
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT FileUtils {
    public:
        /**
         * @brief Constructs a new FileUtils utility.
         */
        FileUtils();
        /**
         * @brief Destructs a FileUtils utility.
         */
        ~FileUtils();

        /**
         * @brief Loads a file and returns its content.
         * @param filename the path to the file
         * @return the content of the file
         */
        static QString load(const QString &filename);

        /**
         * @brief Serializes an IPrintable to a file.
         * @param ip the IPrintable object to serialize
         * @param filename the path to the file
         * @param append appends the content to the already existing file (if any) or overwrite it
         */
        static void save(IPrintable *ip, const QString &filename, bool append = false);

        /**
         * @brief Serializes a QString to a file.
         * @param s the QString to serialize
         * @param filename the path to the file
         * @param append appends the content to the already existing file (if any) or overwrite it
         */
        static void save(const QString &s, const QString &filename, bool append = false);

        /**
         * @brief Removes a file.
         * @param filename the path to the file
         * @return true if successful, false otherwise
         */
        static bool remove(const QString &filename);

        /**
         * @brief Opens a file, and throws an Exception if it fails.
         * @param file the file to open
         * @param mode the opening mode
         */
        static void open(QFile &file, QFile::OpenMode mode);

        /**
         * @brief Closes a file.
         * @param file the file to close
         */
        static void close(QFile &file);

        /**
         * @brief Checks the extension of a filename.
         * Throws an exception if the extension does not correspond.
         * @param filename the path to the file
         * @param extension the file extension to check against
         */
        static void checkExtension(const QString &filename, const QString &extension);

        /**
         * @brief Changes the extension of a filename.
         * @param filename the filename
         * @param extension the extension
         */
        static QString changeExtension(const QString &filename, const QString &extension);

        /**
         * @brief Removes the extension of a filename.
         * @param filename the filename
         */
        static QString removeExtension(const QString &filename);

        /**
         * @brief Checks whether the file exists.
         * Throws an exception if the file was not found.
         * @param filename the path to the file
         */
        static void checkExists(const QString &filename);

        /**
         * @brief Checks whether the directory exists.
         * Throws an exception if the directory was not found.
         * @param path the path to the directory
         */
        static void checkExists(const QDir &path);

        /**
         * @brief Checks whether the filename is valid.
         * Throws an exception if the filename is empty or null.
         * @param filename the path to the file
         */
        static void checkValid(const QString &filename);

        /**
         * @brief Checks whether the file exists.
         * @param filename the path to the file
         * @return a boolean indicating the existence of the file
         */
        static bool exists(const QString &filename);

        /**
         * @brief Checks whether the directory exists.
         * @param path the path to the directory
         * @return a boolean indicating the existence of the directory
         */
        static bool exists(const QDir &path);

        /**
         * @brief Checks whether the filename is valid.
         * @param filename the path to the file
         * @return a boolean indicating the validity of the filename
         */
        static bool isValid(const QString &filename);

        /**
         * @brief Combines a parent directory and a relative child directory.
         * @param parent the parent directory
         * @param path the relative child directory
         * @return the child directory, including the path to the parent directory
         */
        static QDir slashed(const QDir &parent, const QDir &path);

        /**
         * @brief Combines a parent directory and a relative child path.
         * @param parent the parent directory
         * @param path the relative child path
         * @return the complete child path, including the path to the parent directory
         */
        static QString slashed(const QDir &parent, const QString &path);

        /**
         * @brief Combines a parent path and a relative child path.
         * @param parent the parent path
         * @param path the relative child path
         * @return the complete child path, including the parent path
         */
        static QString slashed(const QString &parent, const QString &path);

        /**
         * @brief Returns the path to the directory containing the file.
         * @param filepath the path to the file
         * @return the path to the directory containing the file
         */
        static QString path(const QString &filepath);

        /**
         * @brief Returns the directory containing the file.
         * @param filepath the path to the file
         * @return the directory containing the file
         */
        static QDir dir(const QString &filepath);

        /**
         * @brief Returns the name of the file, removing its absolute or relative path.
         * @param filepath the path to the file
         * @return the name of the file
         */
        static QString filename(const QString &filepath);

        /**
         * @brief Checks whether the path is absolute.
         * @param path the path to check
         * @return a boolean indicating whether the path is absolute or not
         */
        static bool isAbsolute(const QString &path);

        /**
         * @brief Creates a path recursively on the filesystem, using a parent
         * path as the base directory.
         * @param parent the path to the base directory
         * @param path the path to create, relatively to the base directory
         * @return a boolean indicating whether the creation was successful or not
         */
        static bool createPath(const QString &parent, const QString &path);

        /**
         * @brief Creates a path recursively on the filesystem, using a parent
         * path as the base directory, and checks whether the path was effectively
         * created or not. Throws an exception if the path to be created is not found.
         * @param parent the path to the base directory
         * @param path the path to create, relatively to the base directory
         * @return the complete path of the created path
         */
        static QString checkCreatedPathExists(const QString &parent, const QString &path);

        /**
         * @brief Checks whether a directory contains images, using IMG_FORMATS
         * constant to determine the allowed image file extensions.
         * @param dir the directory to test
         * @return a boolean indicating the presence of images
         */
        static bool containsImages(const QDir &dir);
};

#endif /* GEMPP_FILEUTILS_H */
