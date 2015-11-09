#ifndef GEMPP_QLABELITEM_H
#define GEMPP_QLABELITEM_H

#include <QGraphicsSimpleTextItem>
#include <QBrush>
#include <QFont>
#include "../../../Portability.h"

class DLL_EXPORT QLabelItem : public QGraphicsSimpleTextItem {
    public:
        QLabelItem(const QString &text, QGraphicsItem *parent = 0);
        void view(bool visible = true);
};

#endif /* GEMPP_QLABELITEM_H */
