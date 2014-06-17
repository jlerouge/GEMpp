#ifndef _LAYOUTGRAPHELEMENT_H_
#define _LAYOUTGRAPHELEMENT_H_

#include <QObject>
#include <QColor>
#include "../Core/Constants.h"

class DLL_EXPORT LayoutGraphElement {
    public :
        LayoutGraphElement(int size = 10, QColor color = QColor(Qt::white));
        virtual ~LayoutGraphElement();

        int getSize() const ;
        void setSize(int size);
        const QColor &getColor() const;
        void setColor(const QColor &color);

    private :
        QColor color_;
        int size_;
};

#endif /* _LAYOUTGRAPHELEMENT_H_ */
