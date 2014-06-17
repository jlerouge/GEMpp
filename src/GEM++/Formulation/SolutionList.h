#ifndef __SOLUTIONLIST_H__
#define __SOLUTIONLIST_H__

#include "Solution.h"

class DLL_EXPORT SolutionList : virtual public IPrintable, virtual public ISaveable {
    public:
        SolutionList(Formulation *f = 0);
        virtual ~SolutionList();

        void setFormulation(Formulation *f);
        Formulation *getFormulation();
        Solution *newSolution();
        Solution *getSolution(int i);
        int getSolutionCount();
        Solution *lastSolution();

        QList<Solution *>::iterator begin();
        QList<Solution *>::iterator end();

        virtual void print(Printer *p);
        virtual void save(const QString &filename);

    private:
        Formulation *formulation_;
        QList<Solution *> solutions_;
};

#endif /* __SOLUTIONLIST_H__ */
