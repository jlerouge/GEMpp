#include "QLabelItem.h"

QLabelItem::QLabelItem(const QString &text, QGraphicsItem *parent) : QGraphicsSimpleTextItem(text, parent) {
    setFont(QFont("Helvetica", 10));
    setBrush(QBrush(QColor(Qt::black)));
}

void QLabelItem::view(bool visible) {
    QBrush mybrush = brush();
    QColor c = mybrush.color();
    c.setAlpha(visible ? 255 : 0);
    mybrush.setColor(c);
    setBrush(mybrush);
}
