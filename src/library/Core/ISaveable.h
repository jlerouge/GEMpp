#ifndef GEMPP_ISAVEABLE_H
#define GEMPP_ISAVEABLE_H

class QString;
#include "Portability.h"

/**
 * @brief The ISaveable class is an interface for objects
 * that can be saved to plain text files.
 * @warning This interface must be implemented to be used.
 * @see ILoadable
 * @see IPrintable
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT ISaveable {
    public:
        /**
         * @brief Destructs an ISaveable.
         */
        virtual ~ISaveable() {}
        /**
         * @brief Saves an ISaveable to a file.
         * @param filename the path to the file
         */
        virtual void save(const QString &filename) = 0;
};

#endif /*ISAVEABLE_H*/
