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

#include "Printer.h"

class DLL_EXPORT Random {
    public:
        static void seedRand(int seed = -1);

        static double randDouble();
        static double randDouble(double low, double high);
        static int randInt(int low, int high);

        static void randPerm(QVector<int> &v);
        static QVector<int> randPerm(int n);
        static QVector<int> randPerm(int low, int high);

        static QVector<int> id(int n);
        static QVector<int> id(int low, int high);
};

#endif /* RANDOM_H */
