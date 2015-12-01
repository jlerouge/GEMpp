#ifndef GEMPP_MAINWINDOW_H
#define GEMPP_MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include "QGraphWidget.h"
#include "Solver/Matcher.h"
#include "Application/GUIApplication.h"
#include "Application/Widgets/QConfigurationDialog.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow();

    protected:
        virtual void closeEvent(QCloseEvent *e);

    private slots:
        void distance();
        void matching();
        void compute(Problem *pb, Configuration *cfg);

    private:
        void createActions();
        void createMenus();
        void createToolbar();
        void readSettings();
        void writeSettings();

        Matcher *matcher;
        QGraphWidget *viewQuery;
        QGraphWidget *viewTarget;

        QMenu *fileMenu;
        QMenu *computeMenu;
        QMenu *helpMenu;
        QAction *openQueryAct;
        QAction *openTargetAct;
        QAction *graphEditDistanceAct;
        QAction *subgraphMatchingAct;
        QAction *exitAct;
        QAction *aboutAct;
        QAction *aboutQtAct;
};

#endif /* GEMPP_MAINWINDOW_H */
