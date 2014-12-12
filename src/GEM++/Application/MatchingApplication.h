#ifndef __MATCHINGAPPLICATION_H__
#define __MATCHINGAPPLICATION_H__

#include <QQueue>
#include "ConsoleApplication.h"
#include "../Model/GraphList.h"
#include "../Solver/Matcher.h"

class DLL_EXPORT MatchingApplication : public ConsoleApplication {
        Q_OBJECT
    public:
        MatchingApplication(int &argc, char **argv, Problem::Type matchingType = Problem::NONE, bool isMultiMatching = false);
        virtual ~MatchingApplication();

        int match();

    public slots:
        void finished(Problem *pb, double objective);

    protected:
        void addOptions();
        void populate();
        void finalize();
        void initMatrix();
        Matrix<double> *matrix();
        void initConfiguration();
        Configuration *configuration();

        // Weights
        void addSubstitutionOption();
        void addCreationOption();

        // Multiple solutions
        void addNumberOption();
        void addCutOption();

        // Input
        void addExtensionOption();

        // Outputs
        void addOutputDirOption();
        void addProgramOption();
        void addAutoProgramOption();
        void addAutoProgramsOption();
        void addSolutionOption();
        void addAutoSolutionOption();
        void addAutoSolutionsOption();
        void addMatrixOption();

        // Formulations
        void addFormulationOption();
        void addToleranceOption();
        void addInducedOption();

        // Approximation
        void addExplorationOption();

        // Solver
        void addSolverOption();
        void addJobsOption();

    private:
        Problem::Type matchingType_;
        Configuration *cfg_;
        Weights *w_;
        Matrix<double> *matrix_;
        bool isMultiMatching_;
        QQueue< QPair<Graph*, Graph*> > queue_;
        Graph *g1_;
        Graph *g2_;
        GraphList *gl1_;
        GraphList *gl2_;
        bool isPopulating_;
        int finishedCount_;
        int totalCount_;
};

#endif /* __MATCHINGAPPLICATION_H__ */
