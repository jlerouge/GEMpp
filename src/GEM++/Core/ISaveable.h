#ifndef __ISAVEABLE_H__
#define __ISAVEABLE_H__

class QString;
#include "../../Portability.h"

/**
 * @brief The ISaveable class is an interface for saveable objects.
 *
 * These particular objects can be serialized in plain text files.
 *
 * @warning This interface must be implemented to be used.
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

#endif /*__ISAVEABLE_H__*/
