#ifndef _FDLAYOUT_H_
#define _FDLAYOUT_H_

#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <QMatrix>
#include <QPainter>

#include "LayoutGraph.h"
#include "LayoutVertex.h"
#include "LayoutEdge.h"

typedef struct
{
        QVector2D pos_;
        LayoutVertex *vertex_;
} LayoutVertex_t;

typedef struct
{
        QVector2D origin_;
        QVector2D target_;
        LayoutEdge *edge_;
} LayoutEdge_t;

class DLL_EXPORT ForceDirectedLayout : public QWidget
{
    public :
        enum MouseMode{
            NONE,
            DRAG,
            ROTATE,
            MOVE_VERTEX,
            MOVE_EDGE
        };

        ForceDirectedLayout(QWidget *parent = 0);
        virtual ~ForceDirectedLayout();

        void reset();
        LayoutGraph *getGraph();
        void setGraph(LayoutGraph *graph);

    protected :
        LayoutGraph *graph_;
        virtual void paintEvent(QPaintEvent *paintEvent);
        virtual void keyPressEvent(QKeyEvent *e);
        virtual void mousePressEvent(QMouseEvent *e);
        virtual void mouseReleaseEvent(QMouseEvent *e);
        virtual void mouseMoveEvent(QMouseEvent *e);
        virtual void wheelEvent(QWheelEvent *e);
        virtual void focusInEvent(QFocusEvent *e);
        virtual void focusOutEvent(QFocusEvent *e);
        virtual void prepareRendering(QList<LayoutVertex_t> &vertices, QList<LayoutEdge_t> &edges);
        virtual void clickedVertex(LayoutVertex *clicked) = 0;
        virtual void clickedEdge(LayoutEdge *clicked) = 0;

    private :
        void startMoving(QMouseEvent *me, MouseMode m, Qt::CursorShape shape);
        void stopMoving();
        void zoom(bool in = true);
        QMatrix transformationMatrix(QPoint offset = QPoint(0,0));

        LayoutVertex *movingVertex_;
        MouseMode mouseMode_;
        QPoint moveStart_;
        double rotate_;
        double scale_;
        QPointF translate_;
        bool focus_;
};

#endif /* _FDLAYOUT_H_ */
