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

        void setX(qreal x);
        void setY(qreal y);
        void setWidth(qreal width);
        void setHeight(qreal height);
        qreal x() const;
        qreal y() const;
        qreal width() const;
        qreal height() const;

        void setLeft(qreal left);
        void setRight(qreal right);
        void setTop(qreal top);
        void setBottom(qreal bottom);
        qreal left() const;
        qreal right() const;
        qreal top() const;
        qreal bottom() const;

        void translate(QPointF t, QSizeF size);

        void fit(QSizeF size);
};

#endif /* __QVERTEXITEM_H__ */
