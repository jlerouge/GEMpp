#ifndef __QVERTEXITEM_H__
#define __QVERTEXITEM_H__

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include "../../../Portability.h"

class DLL_EXPORT QVertexItem : public QGraphicsRectItem {
    public:
        QVertexItem(QRectF rect);
        QColor getColor();
        void setColor(QColor color);
        void invertColor();
        void view(bool visible = true);
        void select(bool selected = true);
};

#endif /* __QVERTEXITEM_H__ */
