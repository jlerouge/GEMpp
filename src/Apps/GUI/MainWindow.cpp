#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow() {
    matcher = new Matcher();

    QWidget *widget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(8);

    viewPattern = new QGraphWidget(widget, QGraphWidget::PATTERN);
    viewTarget = new QGraphWidget(widget, QGraphWidget::TARGET);

    gridLayout->addWidget(viewPattern, 0, 0);
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
    delete viewPattern;
    delete viewTarget;
    delete matcher; // FIXME
    writeSettings();
}

void MainWindow::createActions() {
    openPatternAct = new QAction(QIcon(":/images/open1.png"), tr("Open &pattern graph"), this);
    openPatternAct->setShortcut(QKeySequence(tr("Ctrl+P")));
    openPatternAct->setStatusTip(tr("Load the pattern graph from an existing file"));
    connect(openPatternAct, SIGNAL(triggered()), viewPattern, SLOT(open()));

    openTargetAct = new QAction(QIcon(":/images/open2.png"), tr("Open &target graph"), this);
    openTargetAct->setShortcut(QKeySequence(tr("Ctrl+T")));
    openTargetAct->setStatusTip(tr("Load the target graph from an existing file"));
    connect(openTargetAct, SIGNAL(triggered()), viewTarget, SLOT(open()));

    graphEditDistanceAct = new QAction(QIcon(":/images/compute.png"), tr("Graph edit distance"), this);
    graphEditDistanceAct->setShortcut(QKeySequence(tr("Ctrl+D")));
    graphEditDistanceAct->setStatusTip(tr("Computes the graph edit distance between the two graphs"));
    connect(graphEditDistanceAct, SIGNAL(triggered()), this, SLOT(distance()));

    subgraphIsomorphismAct = new QAction(QIcon(":/images/compute.png"), tr("Subgraph isomorphism"), this);
    subgraphIsomorphismAct->setShortcut(QKeySequence(tr("Ctrl+I")));
    subgraphIsomorphismAct->setStatusTip(tr("Look for an isomorphism between the pattern and a subgraph of the target"));
    connect(subgraphIsomorphismAct, SIGNAL(triggered()), this, SLOT(isomorphism()));

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
    fileMenu->addAction(openPatternAct);
    fileMenu->addAction(openTargetAct);
    fileMenu->addAction(exitAct);

    computeMenu = menuBar()->addMenu(tr("&Compute"));
    computeMenu->addAction(graphEditDistanceAct);
    computeMenu->addAction(subgraphIsomorphismAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolbar() {
    QToolBar *toolbar = new QToolBar("Outils", this);
    toolbar->addAction(openPatternAct);
    toolbar->addAction(openTargetAct);
    addToolBar(Qt::TopToolBarArea, toolbar);
}

void MainWindow::distance() {
    if(!viewPattern->getGraph() || !viewTarget->getGraph())
        GEM_exception("You must load pattern and target graphs first.");
    Problem *pb = new Problem(Problem::GED, viewPattern->getGraph(), viewTarget->getGraph());
    QConfigurationDialog cd(pb, "Graph Edit Distance");
    connect(&cd, SIGNAL(compute(Problem*,Configuration*)), this, SLOT(compute(Problem*,Configuration*)));
    cd.exec();
    activateWindow();
}

void MainWindow::isomorphism() {
    if(!viewPattern->getGraph() || !viewTarget->getGraph())
        GEM_exception("You must load pattern and target graphs first.");

    if(!viewPattern->getSubgraph()) {
        if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Query graph",
                                            "Would you like to use the complete\n"
                                            "pattern graph for your query ?",
                                            QMessageBox::Yes|QMessageBox::No).exec()) {
            viewPattern->selectSubgraph(0, -1);
        } else
            GEM_exception("You must select a subgraph on the pattern first.");
    }

    Problem *pb = new Problem(Problem::SUBGRAPH, viewPattern->getSubgraph(), viewTarget->getGraph());
    QConfigurationDialog cd(pb, "Subgraph Isomorphism");
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
