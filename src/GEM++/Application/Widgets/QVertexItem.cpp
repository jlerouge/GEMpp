#include "QVertexItem.h"

QVertexItem::QVertexItem(QRectF rect) : QGraphicsRectItem(rect) {
    QPen mypen = pen();
    mypen.setWidth(3);
    setPen(mypen);
    setColor(QColor(Qt::red));
    select(false);
    view(true);
}

QColor QVertexItem::getColor() {
    return pen().color();
}

void QVertexItem::setColor(QColor color) {
    QPen mypen = pen();
    mypen.setColor(color);
    setPen(mypen);
}

void QVertexItem::invertColor() {
    QPen mypen = pen();
    QColor c = mypen.color();
    c.setRgb(255-c.red(), 255-c.green(), 255-c.blue());
    mypen.setColor(c);
    setPen(mypen);
}

void QVertexItem::view(bool visible) {
    QPen mypen = pen();
    QColor c = mypen.color();
    c.setAlpha(visible ? 255 : 0);
    mypen.setColor(c);
    setPen(mypen);
}

void QVertexItem::select(bool selected) {
    QColor c = pen().color();
    c.setAlpha(selected ? 128 : 0);
    setBrush(QBrush(c));
}
