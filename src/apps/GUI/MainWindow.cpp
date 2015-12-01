#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow() {
    matcher = new Matcher();

    QWidget *widget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(8);

    viewQuery = new QGraphWidget(widget, QGraphWidget::PATTERN);
    viewTarget = new QGraphWidget(widget, QGraphWidget::TARGET);

    gridLayout->addWidget(viewQuery, 0, 0);
    gridLayout->addWidget(viewTarget, 0, 1);
    widget->setLayout(gridLayout);
    setCentralWidget(widget);

    createActions();
    createMenus();
    createToolbar();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent *e) {
    Q_UNUSED(e);
    delete viewQuery;
    delete viewTarget;
    delete matcher; // FIXME
    writeSettings();
}

void MainWindow::createActions() {
    openQueryAct = new QAction(QIcon(":/images/open1.png"), tr("Open &query graph"), this);
    openQueryAct->setShortcut(QKeySequence(tr("Ctrl+P")));
    openQueryAct->setStatusTip(tr("Load the query graph from an existing file"));
    connect(openQueryAct, SIGNAL(triggered()), viewQuery, SLOT(open()));

    openTargetAct = new QAction(QIcon(":/images/open2.png"), tr("Open &target graph"), this);
    openTargetAct->setShortcut(QKeySequence(tr("Ctrl+T")));
    openTargetAct->setStatusTip(tr("Load the target graph from an existing file"));
    connect(openTargetAct, SIGNAL(triggered()), viewTarget, SLOT(open()));

    graphEditDistanceAct = new QAction(QIcon(":/images/compute.png"), tr("Graph edit distance"), this);
    graphEditDistanceAct->setShortcut(QKeySequence(tr("Ctrl+D")));
    graphEditDistanceAct->setStatusTip(tr("Computes the graph edit distance between the two graphs"));
    connect(graphEditDistanceAct, SIGNAL(triggered()), this, SLOT(distance()));

    subgraphMatchingAct = new QAction(QIcon(":/images/compute.png"), tr("Subgraph matching"), this);
    subgraphMatchingAct->setShortcut(QKeySequence(tr("Ctrl+I")));
    subgraphMatchingAct->setStatusTip(tr("Look for a matching between the query and a subgraph of the target"));
    connect(subgraphMatchingAct, SIGNAL(triggered()), this, SLOT(matching()));

    exitAct = new QAction(QIcon(":/images/exit.png"), tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit this application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
    aboutAct->setShortcuts(QKeySequence::HelpContents);
    aboutAct->setStatusTip(tr("Show information about this application"));
    connect(aboutAct, SIGNAL(triggered()), GUIApplication::instance(), SLOT(about()));

    aboutQtAct = new QAction(QIcon(":/images/qt.png"), tr("About Qt"), this);
    aboutQtAct->setStatusTip(tr("Show information about the Qt framework"));
    connect(aboutQtAct, SIGNAL(triggered()), GUIApplication::instance(), SLOT(aboutQt()));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openQueryAct);
    fileMenu->addAction(openTargetAct);
    fileMenu->addAction(exitAct);

    computeMenu = menuBar()->addMenu(tr("&Compute"));
    computeMenu->addAction(graphEditDistanceAct);
    computeMenu->addAction(subgraphMatchingAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolbar() {
    QToolBar *toolbar = new QToolBar("Outils", this);
    toolbar->addAction(openQueryAct);
    toolbar->addAction(openTargetAct);
    addToolBar(Qt::TopToolBarArea, toolbar);
}

void MainWindow::distance() {
    if(!viewQuery->getGraph() || !viewTarget->getGraph())
        Exception("You must load query and target graphs first.");
    Problem *pb = new Problem(Problem::GED, viewQuery->getGraph(), viewTarget->getGraph());
    QConfigurationDialog cd(pb, "Graph Edit Distance");
    connect(&cd, SIGNAL(compute(Problem*,Configuration*)), this, SLOT(compute(Problem*,Configuration*)));
    cd.exec();
    activateWindow();
}

void MainWindow::matching() {
    if(!viewQuery->getGraph() || !viewTarget->getGraph())
        Exception("You must load query and target graphs first.");

    if(!viewQuery->getSubgraph()) {
        if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Query graph",
                                            "Would you like to use the complete\n"
                                            "query graph for your query ?",
                                            QMessageBox::Yes|QMessageBox::No).exec()) {
            viewQuery->selectSubgraph(0, -1);
        } else
            Exception("You must select a subgraph on the query first.");
    }

    Problem *pb = new Problem(Problem::SUBGRAPH, viewQuery->getSubgraph(), viewTarget->getGraph());
    QConfigurationDialog cd(pb, "Subgraph matching");
    connect(&cd, SIGNAL(compute(Problem*,Configuration*)), this, SLOT(compute(Problem*,Configuration*)));
    cd.exec();
    activateWindow();
}

void MainWindow::compute(Problem *pb, Configuration *cfg) {
    SolutionList *sl = new SolutionList();
    matcher->setProblem(pb);
    matcher->setConfiguration(cfg);
    matcher->setOutputSolutionList(sl);
    matcher->run();

    viewTarget->deselect();
    for(int s = 0; s < sl->getSolutionCount(); ++s) {
        QMessageBox::warning(this, QString("Solution %1").arg(s), QString::number(sl->getSolution(s)->getObjective()));
        //viewTarget->map(sol, pb->getType());
    }

    delete pb;
    delete cfg;
    delete sl->getFormulation(); // FIXME
    delete sl;
}

void MainWindow::readSettings()
{
    QSettings settings("LITIS", "GEM++gui");
    QPoint pos = settings.value("pos", QPoint(32, 32)).toPoint();
    QSize size = settings.value("size", QSize(1200, 800)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("LITIS", "GEM++gui");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
