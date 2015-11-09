#ifndef GEMPP__LAYOUTEDGE_H_
#define GEMPP__LAYOUTEDGE_H_

#include "LayoutGraphElement.h"
#include "../Model/Edge.h"

class LayoutVertex;

class DLL_EXPORT LayoutEdge : virtual public Edge, virtual public LayoutGraphElement {
    public :
        LayoutEdge(LayoutVertex *origin, LayoutVertex *target, int size = 15, QColor color = QColor(Qt::white));
        LayoutEdge(const Edge &e);
        virtual ~LayoutEdge();

        static LayoutEdge *upcast(Edge *e);
        static Edge *downcast(LayoutEdge *e);
};

#endif /* GEMPP__LAYOUTEDGE_H_ */
