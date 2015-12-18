#include "QConfigurationDialog.h"

QConfigurationDialog::QConfigurationDialog(Problem *p, QString title) : isMore(false), solver(0), cutMethod(0), number(0), subMethod(0), induced(0), gedMethod(0), pb(p), subsTable(0), creaTable(0), weights(0) {
    setWindowTitle(title+tr(": configuration"));
    setWindowIcon(QIcon(":/images/compute.png"));
    //settings = new QSettings("LITIS", "floorplan-gui");
    settings = new QSettings();
    init();
    if(settings->contains("configuration_size"))
        resize(settings->value("configuration_size").toSize());
    if(settings->contains(QString("%1_fw").arg(Weights::toName(Weights::CREATION).toLower())))
        weights->load(settings->value(QString("%1_fw").arg(Weights::toName(Weights::CREATION).toLower())).toString(), Weights::CREATION);
    if(settings->contains(QString("%1_fw").arg(Weights::toName(Weights::SUBSTITUTION).toLower())))
        weights->load(settings->value(QString("%1_fw").arg(Weights::toName(Weights::SUBSTITUTION).toLower())).toString(), Weights::SUBSTITUTION);
    updateTables();
    resize(minimumSizeHint());
}

QConfigurationDialog::~QConfigurationDialog() {
    if(solver)
        delete solver;
    if(cutMethod)
        delete cutMethod;
    if(number)
        delete number;
    if(subMethod)
        delete subMethod;
    if(induced)
        delete induced;
    if(gedMethod)
        delete gedMethod;
    if(subsTable)
        delete subsTable;
    if(creaTable)
        delete creaTable;
    if(weights)
        delete weights;
    if(settings)
        delete settings;
}

void QConfigurationDialog::init() {
    weights = new Weights();
    QGridLayout *gl = new QGridLayout;
    int row = 0;

    /* Weights parameters */
    initTables();
    // Substitution weights
    subsWeightsTb = new QToolBar("Substitution weights tools", this);
    importFwSubsAct = new QAction(QIcon(":/images/import-fw.png"), tr("Import substitution weights"), this);
    importFwSubsAct->setStatusTip(tr("Imports feature weights configuration file for substitution costs"));
    connect(importFwSubsAct, SIGNAL(triggered()), this, SLOT(loadWeights()));
    exportFwSubsAct = new QAction(QIcon(":/images/export-fw.png"), tr("Export substitution weights"), this);
    exportFwSubsAct->setStatusTip(tr("Exports feature weights configuration file for substitution costs"));
    connect(exportFwSubsAct, SIGNAL(triggered()), this, SLOT(saveWeights()));
    subsWeightsTb->addWidget(new QLabel("Substitution : ", this));
    subsWeightsTb->addAction(importFwSubsAct);
    subsWeightsTb->addAction(exportFwSubsAct);

    // Creation weights
    creaWeightsTb = new QToolBar("Creation weights tools", this);
    importFwCreaAct = new QAction(QIcon(":/images/import-fw.png"), tr("Import creation weights"), this);
    importFwCreaAct->setStatusTip(tr("Imports feature weights configuration file for creation costs"));
    connect(importFwCreaAct, SIGNAL(triggered()), this, SLOT(loadWeights()));
    exportFwCreaAct = new QAction(QIcon(":/images/export-fw.png"), tr("Export creation weights"), this);
    exportFwCreaAct->setStatusTip(tr("Exports feature weights configuration file for creation costs"));
    connect(exportFwCreaAct, SIGNAL(triggered()), this, SLOT(saveWeights()));
    creaWeightsTb->addWidget(new QLabel("Creation : ", this));
    creaWeightsTb->addAction(importFwCreaAct);
    creaWeightsTb->addAction(exportFwCreaAct);

    gl->addWidget(subsWeightsTb, row, 0);
    gl->addWidget(creaWeightsTb, row++, 1);
    gl->addWidget(subsTable, row, 0);
    gl->addWidget(creaTable, row++, 1);

    // Hide additionnal options
    subsWeightsTb->hide();
    creaWeightsTb->hide();
    subsTable->hide();
    creaTable->hide();

    /* Configuration parameters */
    more = new QPushButton("More", this);
    connect(more, SIGNAL(clicked()), this, SLOT(toggleMore()));
    gl->addWidget(more, row, 0, Qt::AlignRight & Qt::AlignBottom);

    QWidget *optionsWidget = new QWidget(this);
    QGridLayout *ogl = new QGridLayout;
    gl->addWidget(optionsWidget, row, 1);
    row = 0;

    // Number of solutions, cut strategy
    number = new QSpinBox(this);
    number->setMinimum(1);
    ogl->addWidget(new QLabel("Number : ", this), row, 0, Qt::AlignRight);
    ogl->addWidget(number, row++, 1);
    cutMethod = new QComboBox(this);
    for(int c = 0; c < Formulation::COUNT; ++c)
        cutMethod->addItem(Formulation::toName((Formulation::CutMethod)c), (Formulation::CutMethod)c);
    cutMethod->setCurrentIndex((int)Formulation::MATCHINGS);
    ogl->addWidget(new QLabel("Cut : ", this), row, 0, Qt::AlignRight);
    ogl->addWidget(cutMethod, row++, 1);

    // Formulation
    if(pb->getType() == Problem::SUBGRAPH) {
        // Induced
        induced = new QCheckBox(this);
        ogl->addWidget(new QLabel("Induced : ", this), row, 0, Qt::AlignRight);
        ogl->addWidget(induced, row++, 1);

        subMethod = new QComboBox(this);
        for(int s = 0; s < SubgraphMatching::COUNT; ++s)
            subMethod->addItem(SubgraphMatching::toName((SubgraphMatching::Method)s), (SubgraphMatching::Method)s);
        subMethod->setCurrentIndex((int)SubgraphMatching::TOPOLOGY);
        ogl->addWidget(new QLabel("Tolerance : ", this), row, 0, Qt::AlignRight);
        ogl->addWidget(subMethod, row++, 1);
    } else if(pb->getType() == Problem::GED) {
        gedMethod = new QComboBox(this);
        for(int g = 0; g < GraphEditDistance::COUNT; ++g)
            gedMethod->addItem(GraphEditDistance::toName((GraphEditDistance::Method)g), (GraphEditDistance::Method)g);
        gedMethod->setCurrentIndex((int)GraphEditDistance::LINEAR);
        ogl->addWidget(new QLabel("Formulation : ", this), row, 0, Qt::AlignRight);
        ogl->addWidget(gedMethod, row++, 1);
    }

    // Solver choice
    solver = new QComboBox(this);
    for(int s = 0; s < Solver::COUNT; ++s)
        solver->addItem(Solver::toName((Solver::Solvers)s));
    solver->setCurrentIndex((int)Solver::GUROBI);
    ogl->addWidget(new QLabel("Solver : ", this), row, 0, Qt::AlignRight);
    ogl->addWidget(solver, row++, 1);
    /* End of configuration parameters */
    optionsWidget->setLayout(ogl);

    /* Control buttons */
    QPushButton *cancel = new QPushButton("Cancel", this);
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    QPushButton *confirm = new QPushButton("Confirm", this);
    connect(confirm, SIGNAL(clicked()), this, SLOT(confirm()));
    ogl->addWidget(cancel, row, 0, Qt::AlignRight);
    ogl->addWidget(confirm, row++, 1);
    more->setFixedWidth(cancel->width());
    /* End of control buttons */

    // Configuration dialog widget
    this->setLayout(gl);
}

void QConfigurationDialog::toggleMore() {
    if((isMore = !isMore)) {
        subsTable->show();
        subsWeightsTb->show();
        creaTable->show();
        creaWeightsTb->show();
        more->setText("Less");
        resize(sizeHint());
    } else {
        subsTable->hide();
        subsWeightsTb->hide();
        creaTable->hide();
        creaWeightsTb->hide();
        more->setText("More");
        resize(minimumSizeHint());
    }
}

void QConfigurationDialog::initTables() {
    Vertex *v = (pb->getQuery()->getVertexCount() > 0)? pb->getQuery()->getVertex(0) : 0;
    Edge *e = (pb->getQuery()->getEdgeCount() > 0)? pb->getQuery()->getEdge(0) : 0;
    int nbAttr = (v ? v->getAttributes().size() : 0) + (e ? e->getAttributes().size() : 0) + 2; // +2 : constants

    subsTable = new QTableWidget(nbAttr, 3, this);
    subsTable->setHorizontalHeaderLabels(QStringList() << "Element" << "Feature" << "Weight");
    creaTable = new QTableWidget(nbAttr, 3, this);
    creaTable->setHorizontalHeaderLabels(QStringList() << "Element" << "Feature" << "Weight");
    int row = 0;
    if(v) {
        QList<QString> attrKeys = v->getAttributes().keys();
        attrKeys.insert(0, GEMPP_CONST_LABEL);
        for(auto att : attrKeys) {
            QString typeIcon = (att.compare(GEMPP_CONST_LABEL) && v->getAttribute(att)->isTextBased())? ":/images/symbolic.png" : ":/images/numeric.png";

            // Substitution
            subsTable->setItem(row, 0, new QTableWidgetItem(QIcon(":/images/vertex.png"), "Vertex"));
            subsTable->item(row, 0)->setFlags(subsTable->item(row, 0)->flags() & ~Qt::ItemIsEditable);

            subsTable->setItem(row, 1, new QTableWidgetItem(QIcon(typeIcon), att));
            subsTable->item(row, 1)->setFlags(subsTable->item(row, 1)->flags() & ~Qt::ItemIsEditable);

            QScienceSpinBox *weight = new QScienceSpinBox(this);
            weight->setMinimum(0);
            weight->setValue(weights->getWeightOrDefault(Weights::SUBSTITUTION, GraphElement::VERTEX, att)->getValue());
            weight->setDecimals(6);
            subsTable->setCellWidget(row, 2, weight);

            // Creation
            creaTable->setItem(row, 0, new QTableWidgetItem(QIcon(":/images/vertex.png"), "Vertex"));
            creaTable->item(row, 0)->setFlags(creaTable->item(row, 0)->flags() & ~Qt::ItemIsEditable);

            creaTable->setItem(row, 1, new QTableWidgetItem(QIcon(typeIcon), att));
            creaTable->item(row, 1)->setFlags(creaTable->item(row, 1)->flags() & ~Qt::ItemIsEditable);

            weight = new QScienceSpinBox(weight);
            weight->setValue(weights->getWeightOrDefault(Weights::CREATION, GraphElement::VERTEX, att)->getValue());
            weight->setDecimals(6);
            creaTable->setCellWidget(row, 2, weight);
            ++row;
        }
    }
    if(e) {
        QList<QString> attrKeys = e->getAttributes().keys();
        attrKeys.insert(0, GEMPP_CONST_LABEL);
        for(auto att : attrKeys) {
            QString typeIcon = (att.compare(GEMPP_CONST_LABEL) && e->getAttribute(att)->isTextBased())? ":/images/symbolic.png" : ":/images/numeric.png";

            // Substitution
            subsTable->setItem(row, 0, new QTableWidgetItem(QIcon(":/images/edge.png"), "Edge"));
            subsTable->item(row, 0)->setFlags(subsTable->item(row, 0)->flags() & ~Qt::ItemIsEditable);

            subsTable->setItem(row, 1, new QTableWidgetItem(QIcon(typeIcon), att));
            subsTable->item(row, 1)->setFlags(subsTable->item(row, 1)->flags() & ~Qt::ItemIsEditable);

            QScienceSpinBox *weight = new QScienceSpinBox(this);
            weight->setMinimum(0);
            weight->setValue(weights->getWeightOrDefault(Weights::SUBSTITUTION, GraphElement::EDGE, att)->getValue());
            weight->setDecimals(6);
            subsTable->setCellWidget(row, 2, weight);

            // Creation
            creaTable->setItem(row, 0, new QTableWidgetItem(QIcon(":/images/edge.png"), "Edge"));
            creaTable->item(row, 0)->setFlags(creaTable->item(row, 0)->flags() & ~Qt::ItemIsEditable);

            creaTable->setItem(row, 1, new QTableWidgetItem(QIcon(typeIcon), att));
            creaTable->item(row, 1)->setFlags(creaTable->item(row, 1)->flags() & ~Qt::ItemIsEditable);

            weight = new QScienceSpinBox(weight);
            weight->setValue(weights->getWeightOrDefault(Weights::CREATION, GraphElement::EDGE, att)->getValue());
            weight->setDecimals(6);
            creaTable->setCellWidget(row, 2, weight);
            ++row;
        }
    }
    subsTable->resizeColumnsToContents();
    subsTable->resizeRowsToContents();
    creaTable->resizeColumnsToContents();
    creaTable->resizeRowsToContents();
}

void QConfigurationDialog::updateTables() {
    Vertex *v = (pb->getQuery()->getVertexCount() > 0)? pb->getQuery()->getVertex(0) : 0;
    Edge *e = (pb->getQuery()->getEdgeCount() > 0)? pb->getQuery()->getEdge(0) : 0;

    int row = 0;
    if(v) {
        QList<QString> attrKeys = v->getAttributes().keys();
        attrKeys.insert(0, GEMPP_CONST_LABEL);
        for(auto att : attrKeys) {
            ((QScienceSpinBox *)subsTable->cellWidget(row, 2))->setValue(weights->getWeightOrDefault(Weights::SUBSTITUTION, GraphElement::VERTEX, att)->getValue());
            ((QScienceSpinBox *)creaTable->cellWidget(row, 2))->setValue(weights->getWeightOrDefault(Weights::CREATION, GraphElement::VERTEX, att)->getValue());
            ++row;
        }
    }
    if(e) {
        QList<QString> attrKeys = e->getAttributes().keys();
        attrKeys.insert(0, GEMPP_CONST_LABEL);
        for(auto att : attrKeys) {
            ((QScienceSpinBox *)subsTable->cellWidget(row, 2))->setValue(weights->getWeightOrDefault(Weights::SUBSTITUTION, GraphElement::EDGE, att)->getValue());
            ((QScienceSpinBox *)creaTable->cellWidget(row, 2))->setValue(weights->getWeightOrDefault(Weights::CREATION, GraphElement::EDGE, att)->getValue());
            ++row;
        }
    }
    subsTable->resizeColumnsToContents();
    subsTable->resizeRowsToContents();
    creaTable->resizeColumnsToContents();
    creaTable->resizeRowsToContents();
}

void QConfigurationDialog::updateWeights() {
    Vertex *v = (pb->getQuery()->getVertexCount() > 0)? pb->getQuery()->getVertex(0) : 0;
    Edge *e = (pb->getQuery()->getEdgeCount() > 0)? pb->getQuery()->getEdge(0) : 0;
    int row = 0;
    if(v) {
        QList<QString> attrKeys = v->getAttributes().keys();
        attrKeys.insert(0, GEMPP_CONST_LABEL);
        for(auto att : attrKeys) {
            weights->getWeightOrDefault(Weights::SUBSTITUTION, GraphElement::VERTEX, att)->setValue(((QScienceSpinBox *)subsTable->cellWidget(row, 2))->value());
            weights->getWeightOrDefault(Weights::CREATION, GraphElement::VERTEX, att)->setValue(((QScienceSpinBox *)creaTable->cellWidget(row, 2))->value());
            ++row;
        }
    }
    if(e) {
        QList<QString> attrKeys = e->getAttributes().keys();
        attrKeys.insert(0, GEMPP_CONST_LABEL);
        for(auto att : attrKeys) {
            weights->getWeightOrDefault(Weights::SUBSTITUTION, GraphElement::EDGE, att)->setValue(((QScienceSpinBox *)subsTable->cellWidget(row, 2))->value());
            weights->getWeightOrDefault(Weights::CREATION, GraphElement::EDGE, att)->setValue(((QScienceSpinBox *)creaTable->cellWidget(row, 2))->value());
            ++row;
        }
    }
}

void QConfigurationDialog::loadWeights(Weights::Operation op) {
    QAction *origin = qobject_cast<QAction *>(sender());
    if(origin) {
        if(origin == importFwSubsAct)
            op = Weights::SUBSTITUTION;
        if(origin == importFwCreaAct)
            op = Weights::CREATION;
    }

    QString att = QString("%1_fw").arg(Weights::toName(op).toLower());
    QString fw = settings->value(att, "/home/foo.bar").toString();
    QString fileName = QFileDialog::getOpenFileName(this, QString("Import %1 feature weights").arg(Weights::toName(op).toLower()), QFileInfo(fw).path(), "Feature weights (*.fw)");
    if(!fileName.isEmpty()) {
        weights->load(fileName, op);
        settings->setValue(att, fileName);
        updateTables();
    }
}

void QConfigurationDialog::saveWeights(Weights::Operation op) {
    QAction *origin = qobject_cast<QAction *>(sender());
    if(origin) {
        if(origin == exportFwSubsAct)
            op = Weights::SUBSTITUTION;
        if(origin == exportFwCreaAct)
            op = Weights::CREATION;
    }

    updateWeights();
    QString att = QString("%1_fw").arg(Weights::toName(op).toLower());
    QString fw = settings->value(att, "/home/foo.bar").toString();
    try {
        QString fileName = QFileDialog::getSaveFileName(this, QString("Export %1 feature weights").arg(Weights::toName(op).toLower()), QFileInfo(fw).path(), "Feature weights (*.fw)");
        if(!fileName.isEmpty()) {
            weights->save(fileName, op);
            settings->setValue(att, fileName);
        }
    } catch (std::logic_error e) {
        QMessageBox::warning(this, tr("Warning"), tr(e.what()));
    }
}

void QConfigurationDialog::confirm() {
    settings->setValue("configuration_size", size());
    Configuration *cfg = new Configuration();
    cfg->solver = solver->currentText();
    cfg->number = number->value();
    cfg->cutMethod = (Formulation::CutMethod)cutMethod->currentData().toInt();

    switch(pb->getType()) {
        case Problem::GED:
            cfg->gedMethod = (GraphEditDistance::Method)gedMethod->currentData().toInt();
            break;
        case Problem::SUBGRAPH:
            cfg->induced = induced->isChecked();
            cfg->subMethod = (SubgraphMatching::Method)subMethod->currentData().toInt();
            break;
        default:
            break;
    }
    cfg->verbose = true;

    updateWeights();
    pb->computeCosts(weights);

    emit compute(pb, cfg);
    accept();
}

void QConfigurationDialog::cancel() {
    settings->setValue("configuration_size", size());
    delete pb;
    reject();
}

QSize QConfigurationDialog::sizeHint() const {
    return QSize(640,480);
}

QSize QConfigurationDialog::minimumSizeHint() const {
    return QSize(320,240);
}
