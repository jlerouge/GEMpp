#ifndef GEMPP_QSUBGRAPHDIALOG_H
#define GEMPP_QSUBGRAPHDIALOG_H

#include <QtWidgets>
#include <QDialog>
#include "Model/Problem.h"

class QSubgraphDialog : public QDialog {
        Q_OBJECT

    public:
        QSubgraphDialog(int vertexIndex);
        ~QSubgraphDialog();

    signals:
        void selectSubgraph(int vertexIndex, int neighborhood);

    private slots:
        void confirm();

    private:
        QSpinBox *number_;
        int vertexIndex_;
};

#endif /* GEMPP_QSUBGRAPHDIALOG_H */
