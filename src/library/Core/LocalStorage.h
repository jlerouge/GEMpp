#ifndef GEMPP_LOCALSTORAGE_H
#define GEMPP_LOCALSTORAGE_H

#include <QUuid>
#include <QStandardPaths>

#include "Constants.h"
#include "Identified.h"
#include "FileUtils.h"

/**
 * @brief The LocalStorage class is a utility that provides access to local
 * application storage. A LocalStorage has a unique ID which identifies the
 * subdirectory in which the files will be stored. This ID should be bound
 * to some group of data or some configuration of the application.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT LocalStorage : public Identified {
public:
    /**
     * @brief Constructs a new LocalStorage utility.
     */
    LocalStorage(const QString &uniqueID = QString());

    /**
     * @brief Constructs a copy of another LocalStorage utility.
     */
    LocalStorage(const LocalStorage &other);

    /**
     * @brief Destructs a LocalStorage utility.
     */
    ~LocalStorage();

    /**
     * @brief Returns the directory of this LocalStorage.
     * @return the directory
     */
    QDir getDir();

    /**
     * @brief Returns the directory path of this LocalStorage.
     * @return the path
     */
    QString getPath();

    /**
     * @brief Tests whether the path of the LocalStorage exists.
     * @return true if it exists, false otherwise
     */
    bool exists();

    /**
     * @brief Deletes all data in the LocalStorage and removes the directory.
     * @return true if the directory has been successfully removed, false otherwise
     */
    bool remove();

    /**
     * @brief Creates the path of the LocalStorage.
     * @return true if the path has been successfully created, false otherwise
     */
    bool create();

    /**
     * @brief Returns a unique identifier, useable for local data storage.
     * @return the identifier
     */
    static QString createUniqueID();

    /**
     * @brief Returns the standard application data directory.
     * @return the directory
     */
    static QDir getLocalDir();

    /**
     * @brief Returns the standard application data directory path.
     * @return the path
     */
    static QString getLocalPath();
};

#endif /* GEMPP_LOCALSTORAGE_H */
