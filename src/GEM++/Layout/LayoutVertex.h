#ifndef GEMPP__LAYOUTVERTEX_H_
#define GEMPP__LAYOUTVERTEX_H_

#include <QVector2D>
#include "LayoutGraphElement.h"
#include "LayoutEdge.h"
#include "../Model/Vertex.h"

class DLL_EXPORT LayoutVertex : virtual public Vertex, virtual public LayoutGraphElement {
    public :
        LayoutVertex(int negativeForce = 50, int size = 15, QColor color = QColor(Qt::yellow));
        LayoutVertex(const Vertex &other);
        virtual ~LayoutVertex();

        QSet<LayoutEdge *> getEdges(Direction d) const;
        const QVector2D &getPosition() const;
        void setPosition(QVector2D position);
        const QVector2D &getForce() const;
        void setForce(QVector2D force);
        double getNegativeForce() const;
        void setNegativeForce(double force);
        bool getLocked() const;
        void setLocked(bool locked);
        void updatePosition();

        static LayoutVertex *upcast(Vertex *v);
        static Vertex *downcast(LayoutVertex *v);

    protected :
        QVector2D pos_;
        QVector2D force_;
        double negativeForce_;
        bool locked_;
};

#endif /* GEMPP__LAYOUTVERTEX_H_ */
