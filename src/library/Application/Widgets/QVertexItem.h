#ifndef GEMPP_QVERTEXITEM_H
#define GEMPP_QVERTEXITEM_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include "Core/Portability.h"

class DLL_EXPORT QVertexItem : public QGraphicsRectItem {
    public:

        friend class QGraphWidget;

        enum MatchStatus {
            UNMATCHED,
            INCORRECT,
            CORRECT
        };

        QVertexItem(QRectF rect);

        MatchStatus getStatus();
        void setStatus(MatchStatus status);

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

    protected:
        void setColor(QColor color);
        QColor getColor();

    private:
        MatchStatus status_;
};

#endif /* GEMPP_QVERTEXITEM_H */
