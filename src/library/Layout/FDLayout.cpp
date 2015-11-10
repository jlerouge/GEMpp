#include "FDLayout.h"

ForceDirectedLayout::ForceDirectedLayout(QWidget *parent) : QWidget(parent) {
    // Black background
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
    setFocusPolicy(Qt::ClickFocus);
    setCursor(QCursor(Qt::ArrowCursor));
    mouseMode_ = NONE;
    movingVertex_ = (LayoutVertex *)0;
    graph_ = (LayoutGraph *)0;
    focus_ = false;
    reset();
}

ForceDirectedLayout::~ForceDirectedLayout() {}

void ForceDirectedLayout::reset() {
    scale_ = 1;
    rotate_ = 0;
    translate_ = QPointF(0,0);
}

LayoutGraph *ForceDirectedLayout::getGraph() {
    return graph_;
}

void ForceDirectedLayout::setGraph(LayoutGraph *graph) {
    reset();
    graph_ = graph;
    if(graph_)
        connect(graph_, SIGNAL(layoutGraphChanged()), this, SLOT(update()));
}

void ForceDirectedLayout::prepareRendering(QList<LayoutVertex_t> &vertices, QList<LayoutEdge_t> &edges) {
    if(graph_) {
        //Set transformation matrix
        QMatrix tfMatrix = transformationMatrix();
        //Transform vertices
        for (auto v : graph_->getVertices()) {
            LayoutVertex_t tVertex;
            qreal x, y;
            tfMatrix.map(v->getPosition().x(), v->getPosition().y(), &x, &y);
            tVertex.pos_ = QVector2D(x,y);
            tVertex.vertex_ = v;
            vertices.append(tVertex);
        }
        //Transform edges
        for(auto e : graph_->getEdges()) {
            LayoutEdge_t	tEdge;
            qreal x, y;
            tfMatrix.map(LayoutVertex::upcast(e->getOrigin())->getPosition().x(),
                         LayoutVertex::upcast(e->getOrigin())->getPosition().y(), &x, &y);
            tEdge.origin_ = QVector2D(x,y);
            tfMatrix.map(LayoutVertex::upcast(e->getTarget())->getPosition().x(),
                         LayoutVertex::upcast(e->getTarget())->getPosition().y(), &x, &y);
            tEdge.target_ = QVector2D(x,y);
            tEdge.edge_ = e;
            edges.append(tEdge);
        }
    }
}

void ForceDirectedLayout::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key_Plus:
            zoom();
            break;
        case Qt::Key_Minus:
            zoom(false);
            break;
        default:
            break;
    }
}

void ForceDirectedLayout::wheelEvent(QWheelEvent *e) {
    zoom(e->angleDelta().y() > 0);
}

void ForceDirectedLayout::focusInEvent(QFocusEvent *) {
    focus_ = true;
}

void ForceDirectedLayout::focusOutEvent(QFocusEvent *) {
    focus_ = false;
}

void ForceDirectedLayout::zoom(bool in) {
    if(focus_) {
        double factor = 0.95;
        scale_ *= (in? (1/factor) : factor);
    }
}

void ForceDirectedLayout::mousePressEvent(QMouseEvent *me) {
    if(graph_ && mouseMode_ == NONE && (me->button() & Qt::LeftButton || me->button() & Qt::RightButton)) {
        qreal x,y;
        QMatrix tfMatrix = transformationMatrix(QPoint(width(), height())/2).inverted();
        tfMatrix.map(me->x(), me->y(), &x, &y);
        for (auto v : graph_->getVertices()) {
            if ((QVector2D(x, y) - v->getPosition()).length() <= v->getSize()/(2*scale_)) {
                if(me->button() & Qt::LeftButton) {
                    startMoving(me, MOVE_VERTEX, Qt::ClosedHandCursor);
                    movingVertex_ = v;
                    v->setLocked(true);
                } else if (me->button() & Qt::RightButton)
                    clickedVertex(v);
                return;
            }
        }
        if(me->button() & Qt::RightButton) {
            for (auto e : graph_->getEdges()) {
                if (false) {
                    clickedEdge(e);
                    return;
                }
            }
        }

        //If no vertex/edge is clicked, move or rotate the view
        if(me->button() & Qt::LeftButton) {
            startMoving(me, DRAG, Qt::SizeAllCursor);
        } else if(me->button() & Qt::RightButton) {
            startMoving(me, ROTATE, Qt::SizeHorCursor);
        }
    }
}

void ForceDirectedLayout::mouseReleaseEvent(QMouseEvent *e) {
    Q_UNUSED(e);
    if (mouseMode_ != NONE)
        stopMoving();
}

void ForceDirectedLayout::mouseMoveEvent(QMouseEvent *e) {
    if (mouseMode_ == DRAG) {
        translate_ += QPointF(e->globalPos() - moveStart_)/scale_;
    } else if (mouseMode_ == ROTATE) {
        rotate_ += (e->globalX() - moveStart_.x())/scale_;
    } else if ((mouseMode_ == MOVE_VERTEX) && movingVertex_) {
        qreal x,y;
        QMatrix tfMatrix = transformationMatrix(QPoint(width(), height())/2).inverted();
        tfMatrix.map(e->x(), e->y(), &x, &y);
        movingVertex_->setPosition(QVector2D(x, y));
    }
    moveStart_ = e->globalPos();
}

void ForceDirectedLayout::paintEvent(QPaintEvent *pE) {
    Q_UNUSED(pE);
    QPainter paint(this);

    if(focus_) {
        paint.setPen(QPen(QColor(Qt::red), 3));
        paint.drawRect(1, 1, width()-3, height()-3);
    }

    if(graph_) {
        QList<LayoutVertex_t> vertices;
        QList<LayoutEdge_t> edges;
        prepareRendering(vertices, edges);
        paint.setRenderHint(QPainter::Antialiasing);

        QFont font = QFont("Helvetica");
        font.setPointSize(8);
        paint.setFont(font);
        //Draw edges (and their labels)
        for (auto e : edges) {
            paint.setPen(QPen(e.edge_->getColor()));
            paint.drawLine((width()/2) + e.origin_.x(), (height()/2) + e.origin_.y(), (width()/2) + e.target_.x(), (height()/2) + e.target_.y());
            // Write labels
            paint.drawText((width() + e.origin_.x() + e.target_.x())/2, (height() + e.origin_.y() + e.target_.y())/2, e.edge_->getID());
        }

        font.setPointSize(8);
        paint.setFont(font);
        //Draw vertices (and their labels)
        for (auto v : vertices) {
            paint.setPen(QColor(Qt::black));
            QRadialGradient gradient(v.pos_.x()+width()/2, v.pos_.y()+height()/2, v.vertex_->getSize()/2, v.pos_.x()+width()/2, v.pos_.y()+height()/2);
            gradient.setColorAt(0, v.vertex_->getColor());
            gradient.setColorAt(1, v.vertex_->getColor().darker(200));
            QBrush brush(gradient);
            paint.setBrush(brush);
            paint.drawEllipse(QRect((width()/2) + v.pos_.x() - (v.vertex_->getSize() / 2), (height()/2) + v.pos_.y() - (v.vertex_->getSize() / 2), v.vertex_->getSize() + 1, v.vertex_->getSize() + 1));
            // Write labels
            paint.setPen(v.vertex_->getColor());
            paint.drawText((width() / 2) + v.pos_.x() + (v.vertex_->getSize() / 2) + 2, (height() / 2) + v.pos_.y() + (v.vertex_->getSize() / 2), v.vertex_->getID());
        }
    }
}

void ForceDirectedLayout::startMoving(QMouseEvent *me, MouseMode m, Qt::CursorShape shape) {
    moveStart_ = me->globalPos();
    grabMouse();
    setMouseTracking(true);
    mouseMode_ = m;
    setCursor(QCursor(shape));
}

void ForceDirectedLayout::stopMoving() {
    releaseMouse();
    setMouseTracking(false);
    mouseMode_ = NONE;
    setCursor(QCursor(Qt::ArrowCursor));
    if(movingVertex_) {
        movingVertex_->setLocked(false);
        movingVertex_ = (LayoutVertex *)0;
    }
}

QMatrix ForceDirectedLayout::transformationMatrix(QPoint offset) {
    QMatrix	tfMatrix;
    tfMatrix.translate(translate_.x()*scale_ + offset.x(), translate_.y()*scale_ + offset.y());
    tfMatrix.scale(scale_,scale_);
    tfMatrix.rotate(rotate_);
    return tfMatrix;
}
