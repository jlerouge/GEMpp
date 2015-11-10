#ifndef GEMPP_SOLUTION_H
#define GEMPP_SOLUTION_H

#include "Formulation.h"
#include "../Core/ICleanable.h"

/**
 * @brief The Solution class represents a feasible solution of a formulation.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT Solution : virtual public IPrintable, virtual public ISaveable, virtual public ICleanable {
    public:
        /**
         * @brief Indicates the status of the solution, as returned by the solver.
         */
        enum Status{
            NOT_SOLVED = 0, /**< the problem was not solved */
            INFEASIBLE, /**< the problem is infeasible */
            UNBOUNDED, /**< the problem is unbounded (the best solution is infinite) */
            SUBOPTIMAL, /**< best solution found after early-stopping the problem solving */
            OPTIMAL, /**< best possible solution */
            COUNT /**< used to iterate on Solution::Status enum */
        };

        /**
         * @brief The names of statuses.
         */
        static const char *statusName[COUNT];

        /**
         * @brief Returns the name of the status.
         * @param status the status
         * @return the name
         */
        static QString toName(Status status);

        /**
         * @brief Retrieves the status from its name.
         * @param name the name
         * @return the status
         */
        static Status fromName(QString name);

        /**
         * @brief Constructs a new Solution object.
         * @param f the formulation which is solved by this solution
         */
        Solution(Formulation *f);

        /**
         * @brief Destructs a Solution object.
         */
        virtual ~Solution();

        /**
         * @brief Adds a variable and its value to the solution.
         * @param v the variable
         * @param value its value
         */
        void addVariable(Variable *v, int value);

        /**
         * @brief Returns the active variables of the solution and their values.
         * @return the variables and their values
         */
        QHash<Variable *, int> &getVariables();

        /**
         * @brief Returns the vertex substitutions.
         * @return the vertex substitutions.
         */
        QMap<int, int> &getXVariables();

        /**
         * @brief Returns the edge substitutions.
         * @return the edge substitutions.
         */
        QMap<int, int> &getYVariables();

        /**
         * @brief Returns the value of a variable in the solution.
         * @param v the variable
         * @return the value
         */
        int getValue(Variable *v);

        /**
         * @brief Sets the status of the solution.
         * @param status the status
         */
        void setStatus(Status status);

        /**
         * @brief Returns the status of the solution.
         * @return the status
         */
        Status getStatus();

        /**
         * @brief Sets the objective value of the solution.
         * @param objective the objective value
         */
        void setObjective(double objective);

        /**
         * @brief Returns the objective value of the solution.
         * @return the objective value
         */
        double getObjective();

        /**
         * @brief Tests whether this solution is really a solution of the problem
         * (i.e. it is suboptimal or optimal) or an invalid solution.
         * @return a boolean
         */
        bool isValid();

        /**
         * @brief Returns the index of the active variable of the solution where one
         * of the involved vertex is known.
         * @param subId the index of the known vertex
         * @param left if true, the known vertex is a query vertex, else it is a target vertex
         * @return the active variable index
         */
        int activeIndex(int subId, bool left);

        virtual void print(Printer *p);

        /**
         * @brief Prints the solution to a printer in an XML format.
         * @param p the printer
         */
        void printSolution(Printer *p);

        virtual void save(const QString &filename);

        virtual void clean();

    private:
        /**
         * @brief The status of the solution.
         */
        Status status_;

        /**
         * @brief The formulation which is solved by this solution.
         */
        Formulation *formulation_;

        /**
         * @brief The active variables of the solution and their values.
         */
        QHash<Variable *, int> variables_;

        /**
         * @brief The vertex substitutions of the solution.
         */
        QMap<int, int> x_variables_;

        /**
         * @brief The edge substitutions of the solution.
         */
        QMap<int, int> y_variables_;

        /**
         * @brief The objective value of the solution.
         */
        double objective_;
};

#endif /* GEMPP_SOLUTION_H */
