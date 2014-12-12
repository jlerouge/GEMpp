#ifndef __ERRORTOLSUBISO_H__
#define __ERRORTOLSUBISO_H__

#include "SubTolSubIso.h"

class DLL_EXPORT ErrorTolerantSubgraphIsomorphism : virtual public SubstitutionTolerantSubgraphIsomorphism{
    public:
        ErrorTolerantSubgraphIsomorphism(Problem *pb, double up, bool induced);
        virtual ~ErrorTolerantSubgraphIsomorphism() {}

    protected:
        virtual void initCosts();
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /*__ERRORTOLSUBISO_H__*/
