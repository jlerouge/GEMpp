#ifndef __EXACTSUBISO_H__
#define __EXACTSUBISO_H__

#include "SubTolSubIso.h"

class DLL_EXPORT ExactSubgraphIsomorphism : virtual public SubstitutionTolerantSubgraphIsomorphism{
    public:
        ExactSubgraphIsomorphism(Problem *pb, bool low, bool induced);
        virtual ~ExactSubgraphIsomorphism() {}

    protected:
        virtual void restrictProblem(double up);

};

#endif /*__EXACTSUBISO_H__*/
