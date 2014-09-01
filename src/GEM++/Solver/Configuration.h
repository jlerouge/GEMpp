#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "../Core/ICleanable.h"
#include "../Model/Problem.h"
#include "../Formulation/GED.h"
#include "../Formulation/SubIso.h"

class DLL_EXPORT Configuration : virtual public IPrintable, virtual public ICleanable {
    public:
        Configuration();
        virtual ~Configuration();

        bool check();
        virtual void clean();
        virtual void print(Printer *p);

        QString substitution;
        QString creation;
        QString outputDir;
        QString program;
        QString solution;
        QString solver;
        QString matrix;
        QString ext;

        bool verbose;
        int number;
        Formulation::CutMethod cutMethod;

        Problem::Type matchingType;
        SubgraphIsomorphism::Method subMethod;
        bool induced;
        GraphEditDistance::Method gedMethod;

        bool lowerbound;
        double upperbound;

        int threadsPerInstance;
        int parallelInstances;

        double timeLimit;
};

#endif /* __CONFIGURATION_H__ */
