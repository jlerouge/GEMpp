#ifndef __SUBTOLSUBISO_H__
#define __SUBTOLSUBISO_H__

#include "SubIso.h"

class DLL_EXPORT SubstitutionTolerantSubgraphIsomorphism : virtual public SubgraphIsomorphism{
    public:
        SubstitutionTolerantSubgraphIsomorphism() {}
        SubstitutionTolerantSubgraphIsomorphism(Problem *pb, bool low, double up, bool induced);
        virtual ~SubstitutionTolerantSubgraphIsomorphism();

    protected:
        virtual void restrictProblem(double up);
        virtual void initConstraints();
};

#endif /*__SUBTOLSUBISO_H__*/
