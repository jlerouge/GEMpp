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
        void isomorphism();
        void compute(Problem *pb, Configuration *cfg);

    private:
        void createActions();
        void createMenus();
        void createToolbar();
        void readSettings();
        void writeSettings();

        Matcher *matcher;
        QGraphWidget *viewPattern;
        QGraphWidget *viewTarget;

        QMenu *fileMenu;
        QMenu *computeMenu;
        QMenu *helpMenu;
        QAction *openPatternAct;
        QAction *openTargetAct;
        QAction *graphEditDistanceAct;
        QAction *subgraphIsomorphismAct;
        QAction *exitAct;
        QAction *aboutAct;
        QAction *aboutQtAct;
};

#endif /* GEMPP_MAINWINDOW_H */
