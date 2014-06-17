#ifndef __QGRAPHWIDGET_H__
#define __QGRAPHWIDGET_H__

#include <QtWidgets>
#include <QFileDialog>
#include "QSubgraphDialog.h"
//#include "QWeightsDialog.h"
#include "Layout/FDLayout.h"
#include "Formulation/Solution.h"
#include "Core/Random.h"

class QGraphWidget : public ForceDirectedLayout {
        Q_OBJECT
    public:
        enum Type{
            PATTERN = 0,
            TARGET,
            COUNT
        };
        static const char *typeNames[COUNT];

        QGraphWidget(QWidget *parent, Type t);
        ~QGraphWidget();
        Graph *getSubgraph();
        void select();
        void deselect();
        //  void map(Solution *sol, Problem::Type mode);

    public slots:
        void open();
        void selectSubgraph(int vertexIndex, int neighborhood);

    protected:
        QSize sizeHint() const;
        virtual void clickedVertex(LayoutVertex *v);
        virtual void clickedEdge(LayoutEdge *e);

    private :
        void loadGraph(const QString &filename);
        void clear();

        Type type_;
        Graph *subgraph_;
};

#endif /* __QGRAPHWIDGET_H__ */
