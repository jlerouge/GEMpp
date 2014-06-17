#ifndef __BIPARTITEGED_H__
#define __BIPARTITEGED_H__

#include "GED.h"

class DLL_EXPORT BipartiteGED: virtual public GraphEditDistance {
    public:
        BipartiteGED(Problem *pb, double up = 1);
        virtual ~BipartiteGED();

        QPair<int, int> updateLowerBound(Solution *sol);

    protected:
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /*__BIPARTITEGED_H__*/
