#ifndef GEMPP_SOLUTIONLIST_H
#define GEMPP_SOLUTIONLIST_H

#include "Solution.h"

/**
 * @brief The SolutionList class represents a list of found solutions
 * for a given formulation.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT SolutionList : virtual public IPrintable, virtual public ISaveable {
    public:
        /**
         * @brief Constructs a new SolutionList object.
         * @param f the formulation which is solved by all the solutions
         */
        SolutionList(Formulation *f = 0);

        /**
         * @brief Destructs a SolutionList object.
         */
        virtual ~SolutionList();

        /**
         * @brief Sets the formulation which is solved by all the solutions of the list.
         * @param f the formulation
         */
        void setFormulation(Formulation *f);

        /**
         * @brief  Returns the formulation which is solved by all the solutions of the list.
         * @return the formulation
         */
        Formulation *getFormulation();

        /**
         * @brief Creates a new solution and adds it to the list.
         * @return the new solution
         */
        Solution *newSolution();

        /**
         * @brief Returns a solution using its index.
         * @param i the index
         * @return the solution
         */
        Solution *getSolution(int i);

        /**
         * @brief Returns the number of solutions in the list.
         * @return the solution count
         */
        int getSolutionCount();

        /**
         * @brief Returns the last solution of the list.
         * @return the last solution
         */
        Solution *lastSolution();

        /**
         * @brief Returns an iterator on the solution list, poiting to the first element.
         * @return an iterator
         */
        QList<Solution *>::iterator begin();

        /**
         * @brief Returns an iterator on the solution list, poiting after the last element.
         * @return an iterator
         */
        QList<Solution *>::iterator end();

        virtual void print(Printer *p);

        virtual void save(const QString &filename);

    private:
        /**
         * @brief The formulation which is solved by all the solutions of the list.
         */
        Formulation *formulation_;

        /**
         * @brief The actual list of solutions.
         */
        QList<Solution *> solutions_;
};

#endif /* GEMPP_SOLUTIONLIST_H */
