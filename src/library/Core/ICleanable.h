#ifndef GEMPP_ICLEANABLE_H
#define GEMPP_ICLEANABLE_H

#include "Constants.h"

/**
 * @brief The ICleanable class is an interface for cleanable objects.
 *
 * Calling the clean() method on an object should have the effect to
 * reset it to its initial state, before reusing it.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @warning This interface must be implemented to be used.
 */
class DLL_EXPORT ICleanable {
    public:
        /**
         * @brief Destructs an ICleanable.
         */
        virtual ~ICleanable() {}

        /**
         * @brief Cleans an ICleanable.
         */
        virtual void clean() = 0;
};

#endif /*ICLEANABLE_H*/
