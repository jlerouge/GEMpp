#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include "Formulation.h"
#include "../Core/ICleanable.h"

class DLL_EXPORT Solution : virtual public IPrintable, virtual public ISaveable, virtual public ICleanable {
    public:
        enum Status{
            NOT_SOLVED = 0,
            INFEASIBLE,
            UNBOUNDED,
            SUBOPTIMAL,
            OPTIMAL,
            COUNT
        };
        static const char *statusName[COUNT];
        static QString toName(Status status);
        static Status fromName(QString name);

        Solution(Formulation *f);
        virtual ~Solution();

        void addVariable(Variable *, int value);
        QHash<Variable *, int> &getVariables();
        QMap<int, int> &getXVariables();
        QMap<int, int> &getYVariables();
        int getValue(Variable *v);
        void setStatus(Status status);
        Status getStatus();
        void setObjective(double objective);
        double getObjective();
        bool isValid();
        int activeIndex(int subId, bool left);

        virtual void print(Printer *p);
        void printSolution(Printer *p);
        virtual void save(const QString &filename);
        virtual void clean();

    private:
        Status status_;
        Formulation *formulation_;
        QHash<Variable *, int> variables_;
        QMap<int, int> x_variables_;
        QMap<int, int> y_variables_;
        double objective_;
};

#endif /* __SOLUTION_H__ */
