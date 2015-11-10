#ifndef GEMPP_ILOADABLE_H
#define GEMPP_ILOADABLE_H

class QString;
#include "Portability.h"

/**
 * @brief The ILoadable class is an interface for objects
 * that can be loaded from plain text files.
 * @see ISaveable
 * @warning This interface must be implemented to be used.
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT ILoadable {
    public:
        /**
         * @brief Destructs an ILoadable.
         */
        virtual ~ILoadable() {}
        /**
         * @brief Loads an ILoadable from a file.
         * @param filename the path to the file
         */
        virtual void load(const QString &filename) = 0;
};

#endif /* GEMPP_ILOADABLE_H */
