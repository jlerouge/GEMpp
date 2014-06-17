#ifndef __QLABELITEM_H__
#define __QLABELITEM_H__

#include <QGraphicsSimpleTextItem>
#include <QBrush>
#include <QFont>
#include "../../../Portability.h"

class DLL_EXPORT QLabelItem : public QGraphicsSimpleTextItem {
    public:
        QLabelItem(const QString &text, QGraphicsItem *parent = 0);
        void view(bool visible = true);
};

#endif /* __QLABELITEM_H__ */
