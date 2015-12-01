#ifndef GEMPP_APPLICATIONFACTORY_H
#define GEMPP_APPLICATIONFACTORY_H

#include "MatchingApplication.h"

class DLL_EXPORT ApplicationFactory {
    public:
        static MatchingApplication *createApplication(int &argc, char **argv, Problem::Type type, bool isMultiMatching);
};

#endif /* GEMPP_APPLICATIONFACTORY_H */
