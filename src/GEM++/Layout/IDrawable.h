#ifndef __IDRAWABLE_H__
#define __IDRAWABLE_H__

#include <QPainter>
#include "../Core/Constants.h"

class GEM_DLLSPEC IDrawable {
    public:
        virtual ~IDrawable() {}
        virtual void draw(QPainter *p) = 0;
};

#endif /*__IDRAWABLE__*/
