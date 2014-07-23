#ifndef __QEDGEITEM_H__
#define __QEDGEITEM_H__

#include <QGraphicsLineItem>
#include <QPen>
#include "QVertexItem.h"

class DLL_EXPORT QEdgeItem : public QGraphicsLineItem {
    public:
        QEdgeItem(QVertexItem *origin, QVertexItem *target);
        QVertexItem *getOrigin();
        QVertexItem *getTarget();
        QColor getColor();
        void setColor(QColor color);
        int getWidth();
        void setWidth(int width);
        void select(bool selected = true);
        void view(bool visible = true);

    private:
        QVertexItem *origin_;
        QVertexItem *target_;
};

#endif /* __QEDGEITEM_H__ */
