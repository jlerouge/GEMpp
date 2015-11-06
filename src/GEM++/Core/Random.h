#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <QtGlobal>
#include <QVector>
#include <ctime>

#if defined(WIN32) || defined(WIN64) // Windows platform
    #include <io.h>
    #include <process.h>
#elif defined(LINUX) && (__GNUC__ >= 4) // Linux platform
    #include <unistd.h>
#endif

#include "../../Portability.h"

/**
 * @brief The Random class is a utility to generate pseudo-random numbers.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT Random {
    public:
        /**
         * @brief Seeds the pseudo-random number generator. A same seed will
         * give the same sequence of numbers. When the seed parameter is negative,
         * a combination of the current time and of the PID of the current program
         * is used to give more "real" random numbers.
         * @param seed the seed of the sequence
         */
        static void seedRand(int seed = -1);

        /**
         * @brief Generates a random real number between 0 and 1.
         * @return a real between 0 and 1
         */
        static double randDouble();

        /**
         * @brief Generates a random real number between lower and upper bounds.
         * @param lower the lower bound
         * @param upper the upper bound
         * @return a real between lower and upper bounds
         */
        static double randDouble(double lower, double upper);

        /**
         * @brief Generates a random integer number between lower and upper bounds.
         * @param lower the lower bound
         * @param upper the upper bound
         * @return an integer between lower and upper bounds
         */
        static int randInt(int lower, int upper);
};

#endif /* __RANDOM_H__ */
