#ifndef GEMPP_MATCHINGAPPLICATION_H
#define GEMPP_MATCHINGAPPLICATION_H

#include <QQueue>
#include "ConsoleApplication.h"
#include "Model/GraphList.h"
#include "Solver/Matcher.h"

/**
 * @brief The MatchingApplication class implements graph matching
 * command-line applications. It defines many options related to
 * graph matching, and it is able to solve any graph matching
 * problem using the Matcher class.
 * @author Julien Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT MatchingApplication : public ConsoleApplication {
        Q_OBJECT
    public:
        /**
         * @brief Constructs a new MatchingApplication object with parameters.
         * @param argc the number of command line arguments
         * @param argv the array of command line arguments
         * @param matchingType the type of problem
         * @param isMultiMatching indicates whether this application deals with only two graphs, or two sets of graphs
         */
        MatchingApplication(int &argc, char **argv, Problem::Type matchingType = Problem::NONE, bool isMultiMatching = false);

        /**
         * @brief Destructs a MatchingApplication object
         */
        virtual ~MatchingApplication();

        /**
         * @brief Runs the matchings using the provided options.
         * @return the exit status
         */
        int match();

    public slots:
        /**
         * @brief Slot that is called when one matching is finished.
         * This resulting objective is stored, and other matchings
         * solving are started, if any.
         */
        void finished(Problem *pb, double objective);

        /**
         * @brief Solves a subproblem coming from a parent ::Problem dealing
         * with hierarchical ::Graphs, using the same ::Configuration as for the
         * original ::Problem.
         * @param subproblem the subproblem to solve
         * @param type the ::GraphElement::Type containing the hierarchical subgraphs
         * @param iQuery the index of the query ::GraphElement
         * @param iTarget the index of the target ::GraphElement
         */
        void solveSubProblem(Problem *subproblem, Weights *weights, GraphElement::Type type, int iQuery, int iTarget);

    protected:
        /**
         * @brief Add all default options, depending on the values of
         * isMultiMatching_ and matchingType_.
         */
        void addOptions();

        /**
         * @brief Populates a thread pool with runnable matchers.
         */
        void populate();

        /**
         * @brief Last method called before exiting, saves or displays
         * the distance matrix depending on the options.
         */
        void finalize();

        /**
         * @brief Initializes the distance matrix.
         */
        void initMatrix();

        /**
         * @brief Returns the distance matrix.
         * @return the distance matrix
         */
        Matrix<double> *matrix();

        /**
         * @brief Initializes the matching configuration,
         * using command line arguments
         */
        void initConfiguration();

        /**
         * @brief Returns the matching configuration.
         * @return the matching configuration
         */
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
        /**
         * @brief The type of matching problem.
         */
        Problem::Type matchingType_;

        /**
         * @brief The matching configuration.
         */
        Configuration *cfg_;

        /**
         * @brief The attributes weights.
         */
        Weights *w_;

        /**
         * @brief The distance matrix.
         */
        Matrix<double> *matrix_;

        /**
         * @brief Indicates whether this application deals with only two graphs, or two sets of graphs
         */
        bool isMultiMatching_;

        /**
         * @brief The waiting queue for pairs of graph to match.
         */
        QQueue< QPair<Graph*, Graph*> > queue_;

        /**
         * @brief The query graph.
         */
        Graph *g1_;

        /**
         * @brief The target graph.
         */
        Graph *g2_;

        /**
         * @brief The set of query graphs.
         */
        GraphList *gl1_;

        /**
         * @brief The set of target graphs.
         */
        GraphList *gl2_;

        /**
         * @brief The number of already solved problems.
         */
        int finishedCount_;

        /**
         * @brief The total number of problems to solve.
         */
        int totalCount_;

        /**
         * @brief A mutex to lock the counter incrementation.
         */
        QMutex *mutex_;
};

#endif /* GEMPP_MATCHINGAPPLICATION_H */
