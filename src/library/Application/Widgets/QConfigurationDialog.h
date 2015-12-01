#ifndef GEMPP_QCONFIGURATIONDIALOG_H
#define GEMPP_QCONFIGURATIONDIALOG_H

#include <QtWidgets>
#include "QScienceSpinBox.h"
#include "Solver/Solver.h"
#include "Formulation/GED.h"
#include "Formulation/SubgraphMatching.h"
#include "Model/WeightHash.h"

class DLL_EXPORT QConfigurationDialog : public QDialog {
        Q_OBJECT

    friend class MainWindow;

    public:
        QConfigurationDialog(Problem *pb, QString title);
        ~QConfigurationDialog();

        QSize sizeHint() const;
        QSize minimumSizeHint() const;

    signals:
        void compute(Problem *pb, Configuration *cfg);

    protected slots:
        void confirm();
        void cancel();

    private slots:
        void loadWeights(Weights::Operation op = Weights::SUBSTITUTION);
        void saveWeights(Weights::Operation op = Weights::SUBSTITUTION);
        void toggleMore();

    private:
        void init();
        void initTables();
        void updateTables();
        void updateWeights();

        bool isMore;

        QSettings *settings;
        QComboBox *solver;
        QComboBox *cutMethod;
        QSpinBox *number;
        QComboBox *subMethod;
        QCheckBox *induced;
        QComboBox *gedMethod;
        Problem *pb;

        QAction *importFwSubsAct;
        QAction *importFwCreaAct;
        QAction *exportFwSubsAct;
        QAction *exportFwCreaAct;
        QTableWidget *subsTable;
        QTableWidget *creaTable;
        Weights *weights;

        QToolBar *subsWeightsTb;
        QToolBar *creaWeightsTb;
        QPushButton *more;
};

#endif /* GEMPP_QCONFIGURATIONDIALOG_H */
