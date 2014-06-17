#include "QSubgraphDialog.h"

QSubgraphDialog::QSubgraphDialog(int id) : QDialog(0) {
    vertexIndex_ = id;

    setWindowTitle("Subgraph selection");
    setWindowIcon(QIcon(":/images/compute.png"));

    QGridLayout *gl = new QGridLayout;
    number_ = new QSpinBox(this);
    number_->setMinimum(1);
    number_->setMaximum(5);
    QLabel *neighborhood = new QLabel("Neighborhood : ", this);

    QPushButton *confirm = new QPushButton("Confirm", this);
    connect(confirm, SIGNAL(clicked()), this, SLOT(confirm()));

    gl->addWidget(neighborhood, 0, 0);
    gl->addWidget(number_, 0, 1);
    gl->addWidget(confirm, 1, 1, Qt::AlignRight);

    this->setLayout(gl);
    setMinimumWidth(230);
}

QSubgraphDialog::~QSubgraphDialog() {
    if(number_)
        delete number_;
}

void QSubgraphDialog::confirm() {
    emit selectSubgraph(vertexIndex_, number_->value());
    accept();
}
