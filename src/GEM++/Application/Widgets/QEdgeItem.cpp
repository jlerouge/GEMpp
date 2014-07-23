#include "QEdgeItem.h"

QEdgeItem::QEdgeItem(QVertexItem *origin, QVertexItem *target) : QGraphicsLineItem() {
    setLine(QLine(origin->rect().x()+origin->rect().width()/2, origin->rect().y()+origin->rect().height()/2, target->rect().x()+target->rect().width()/2, target->rect().y()+target->rect().height()/2));
    origin_ = origin;
    target_ = target;
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

QVertexItem *QEdgeItem::getOrigin() {
    return origin_;
}

QVertexItem *QEdgeItem::getTarget() {
    return target_;
}
