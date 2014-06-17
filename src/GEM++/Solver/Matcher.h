#ifndef __MATCHER_H__
#define __MATCHER_H__

#include <QObject>
#include <QRunnable>
#include "Configuration.h"
#include "PluginLoader.h"
#include "../Core/ICleanable.h"
#include "../Formulation/LinearGED.h"
#include "../Formulation/QuadraticGED.h"
#include "../Formulation/BipartiteGED.h"
#include "../Formulation/BipartiteEdges.h"
#include "../Formulation/ErrorTolSubIso.h"
#include "../Formulation/ExactSubIso.h"
#include "../Formulation/SolutionList.h"

class DLL_EXPORT Matcher : public QObject, virtual public QRunnable, virtual public ICleanable {
        Q_OBJECT
    public:
        Matcher();
        Matcher(Problem *pb, Configuration *cfg);
        virtual ~Matcher();

        void setProblem(Problem *pb);
        Problem *getProblem();
        void setConfiguration(Configuration *cfg);
        Configuration *getConfiguration();

        double getObjective();
        void setOutputSolutionList(SolutionList *slout);

    public slots:
        virtual void run();
        void run(SolutionList *slout);
        virtual void clean();

    signals:
        void finished(Problem *pb, double objective);

    private:
        Problem *pb_;
        Configuration *cfg_;
        Solver *s_;
        double obj_;
        SolutionList *slout_;

        void initBipartiteCosts();
        void outputColGenIteration(int iteration, double limit);
        void outputRowGenIteration(int iteration, int generated, QPair<int, int> nb);
};

#endif /* __MATCHER_H__ */
