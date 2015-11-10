#ifndef PIVAJ_LOCALSTORAGE_H
#define PIVAJ_LOCALSTORAGE_H

#include <QUuid>
#include <QStandardPaths>

#include "Constants.h"
#include "Identified.h"
#include "FileUtils.h"

namespace PIVAJ {
    /**
     * @brief The LocalStorage class is a utility that provides
     * access to PIVAJ local storage.
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

            QDir getDir();
            QString getPath();

            bool exists();
            bool remove();
            bool create();

            /**
             * @brief Returns a unique identifier,
             * useable for local data storage.
             * @return the identifier
             */
            static QString createUniqueID();

            static QDir getLocalDir();

            static QString getLocalPath();
    };
}

#endif /* PIVAJ_LOCALSTORAGE_H */
