#ifndef __ICLEANABLE_H__
#define __ICLEANABLE_H__

#include "Constants.h"

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

#endif /*__ICLEANABLE_H__*/
