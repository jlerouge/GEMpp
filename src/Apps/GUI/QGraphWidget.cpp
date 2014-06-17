#include "QGraphWidget.h"

const char *QGraphWidget::typeNames[QGraphWidget::COUNT] = {
    "pattern",
    "target"
};

QGraphWidget::QGraphWidget(QWidget *parent, Type t) : ForceDirectedLayout(parent) {
    type_ = t;
    subgraph_ = (Graph *)0;
}

QGraphWidget::~QGraphWidget() {}

void QGraphWidget::clear() {
    if(graph_) {
        graph_->stop();
        delete graph_;
        graph_ = (LayoutGraph *)0;
    }
    if(subgraph_) {
        delete subgraph_;
        subgraph_ = (Graph *)0;
    }
}

void QGraphWidget::select() {
    for(auto v : subgraph_->getVertices())
        LayoutVertex::upcast(v)->setColor(QColor(Qt::red));
}

void QGraphWidget::deselect() {
    for(auto v : graph_->getVertices())
        v->setColor(QColor(Qt::yellow));
}

Graph *QGraphWidget::getSubgraph() {
    return subgraph_;
}

void QGraphWidget::selectSubgraph(int vertexIndex, int neighborhood) {
    deselect();
    if(subgraph_)
        delete subgraph_;
    subgraph_ = graph_->neighborhoodSubgraph(vertexIndex, neighborhood);
    select();
}

//void QGraphWidget::map(Solution *sol, Problem::Type mode) {
//    switch(mode) {
//        case Problem::GED:
//            if(graph) {
//                for(int i=0; i < graph->getVertexCount(); ++i) {
//                    int index = sol->activeIndex(i, type_ == PATTERN);
//                    labels[i]->setText((index != -1)?QString::number(index):"C");
//                }
//            }
//            break;
//        case Problem::SUBGRAPH:
//            for(auto it : labels)
//                it->setText("");
//            if(type_ == TARGET && graph) {
//                for(auto v : sol->getVariables().keys()) {
//                    QStringList sl;
//                    if(v->getID().startsWith("x")) {
//                        sl = v->getID().mid(2).split(',');
//                        vertices[sl[1].toInt()]->select(true);
//                    }
//                }
//            }
//        default:
//            break;
//    }
//}

void QGraphWidget::open() {
    QSettings settings("LITIS", "GEM++gui");
    QString root;
    #if defined(LINUX)
        root = "/home";
    #elif defined(WIN32)
        root = "C:\\";
    #endif
    QString graphPath = settings.value(QString("%1_graph_path").arg(typeNames[type_]), root).toString();
    QString fileName = QFileDialog::getOpenFileName(this, "Open a graph file", graphPath, "Graph *.gml/*.gxl (*.gml *.gxl)");
    if(!fileName.isEmpty()) {
        loadGraph(fileName);
        settings.setValue(QString("%1_graph_path").arg(typeNames[type_]), QFileInfo(fileName).path());
    }
}

void QGraphWidget::clickedVertex(LayoutVertex *v) {
    QSubgraphDialog *sd = new QSubgraphDialog(v->getIndex());
    connect(sd, SIGNAL(selectSubgraph(int,int)), this, SLOT(selectSubgraph(int,int)));
    sd->exec();
    activateWindow();
    delete sd;
}

void QGraphWidget::clickedEdge(LayoutEdge *e) {
    QMessageBox::warning(this, "Clicked an edge", e->getID());
}

void QGraphWidget::loadGraph(const QString &filename) {
    clear();
    LayoutGraph *lg = new LayoutGraph(filename, this);
    setGraph(lg);
    for(auto v : lg->getVertices())
        v->setPosition(QVector2D(Random::randDouble(-0.25, 0.25)*width(), Random::randDouble(-0.25, 0.25)*height()));
    lg->start(15);
}

QSize QGraphWidget::sizeHint() const {
    return QSize(600,800);
}
