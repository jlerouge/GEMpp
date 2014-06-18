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

void QVertexItem::setX(qreal x) {
    if(x >= 0)
        setRect(x, y(), width(), height());
}

void QVertexItem::setY(qreal y) {
    if(y >= 0)
        setRect(x(), y, width(), height());
}

void QVertexItem::setWidth(qreal width) {
    if(x() >= 0)
        setRect(x(), y(), width, height());
}

void QVertexItem::setHeight(qreal height) {
    if(y() >= 0)
        setRect(x(), y(), width(), height);
}

qreal QVertexItem::x() const {
    return rect().x();
}

qreal QVertexItem::y() const {
    return rect().y();
}

qreal QVertexItem::width() const {
    return rect().width();
}

qreal QVertexItem::height() const {
    return rect().height();
}

void QVertexItem::setLeft(qreal left) {
    if(left >= 0) {
        setWidth(width()+x()-left);
        setX(left);
    }
}

void QVertexItem::setRight(qreal right) {
    setWidth(right-left());
}

void QVertexItem::setTop(qreal top) {
    if(top >= 0) {
        setHeight(height()+y()-top);
        setY(top);
    }
}

void QVertexItem::setBottom(qreal bottom) {
    setHeight(bottom-top());
}

qreal QVertexItem::left() const {
    return x();
}

qreal QVertexItem::right() const {
    return x()+width();
}

qreal QVertexItem::top() const {
    return y();
}

qreal QVertexItem::bottom() const {
    return y()+height();
}

void QVertexItem::translate(QPointF t, QSizeF size) {
    if(left()+t.x() >= 0 && right()+t.x() <= size.width() &&
            top()+t.y() >= 0 && bottom()+t.y() <= size.height()) {
        setX(x()+t.x());
        setY(y()+t.y());
    }
}

void QVertexItem::fit(QSizeF size) {
    setWidth(qMin(width(), size.width() - x()));
    setHeight(qMin(height(), size.height() - y()));
}
