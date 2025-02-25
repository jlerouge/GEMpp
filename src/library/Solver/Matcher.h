#ifndef GEMPP_MATCHER_H
#define GEMPP_MATCHER_H

#include <QObject>
#include <QRunnable>
#include "Configuration.h"
#include "PluginLoader.h"
#include "Core/ICleanable.h"
#include "Formulation/LinearGED.h"
#include "Formulation/BipartiteGED.h"
#include "Formulation/BipartiteEdges.h"
#include "Formulation/MCSM.h"
#include "Formulation/SubgraphIsomorphism.h"
#include "Formulation/SolutionList.h"

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

#endif /* GEMPP_MATCHER_H */
