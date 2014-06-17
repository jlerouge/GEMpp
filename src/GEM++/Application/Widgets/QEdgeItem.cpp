#include "QEdgeItem.h"

QEdgeItem::QEdgeItem(QVertexItem *f, QVertexItem *t) : QGraphicsLineItem() {
    setLine(QLine(f->rect().x()+f->rect().width()/2, f->rect().y()+f->rect().height()/2, t->rect().x()+t->rect().width()/2, t->rect().y()+t->rect().height()/2));
    from = f;
    to = t;
    setPen(QPen(QColor(Qt::blue)));
    select(false);
    view(true);
}

QColor QEdgeItem::getColor() {
    return pen().color();
}

void QEdgeItem::setColor(QColor color) {
    QPen mypen = pen();
    mypen.setColor(color);
    setPen(mypen);
}

int QEdgeItem::getWidth() {
    return pen().width();
}

void QEdgeItem::setWidth(int width) {
    QPen mypen = pen();
    mypen.setWidth(width);
    setPen(mypen);
}

void QEdgeItem::select(bool selected) {
    setWidth(selected ? 8 : 4);
}

void QEdgeItem::view(bool visible) {
    QPen mypen = pen();
    QColor c = mypen.color();
    c.setAlphaF(visible);
    mypen.setColor(c);
    setPen(mypen);
}
