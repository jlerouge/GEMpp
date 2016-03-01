#include "GED.h"

const char* GraphEditDistance::methodName[GraphEditDistance::COUNT] = {
    "Linear",
    "Bipartite"
};

GraphEditDistance::Method GraphEditDistance::fromName(QString name) {
    for(Method m = (Method)0; m < COUNT; m = (Method)((int)m + 1))
        if(QString(methodName[m]).startsWith(name, Qt::CaseInsensitive))
            return m;
    Exception(QString("Formulation '%1' not recognized, please use l(inear), q(uadratic) or b(ipartite).").arg(name));
    return COUNT;
}

QString GraphEditDistance::toName(Method method) {
    return methodName[method];
}

GraphEditDistance::~GraphEditDistance() {
    for(auto v : x_variables)
        for(auto it : v)
            delete it;
}

void GraphEditDistance::initVariables() {
    QString id;
    x_variables = Matrix<Variable*>(nVP, nVT);
    for(i=0; i < nVP; ++i) {
        for(k=0; k < nVT; ++k) {
            id = QString("x_%1,%2").arg(i).arg(k);
            x_variables.setElement(i, k, new Variable(id));
        }
    }
}

void GraphEditDistance::initCosts() {
    x_costs = Matrix<double>(nVP, nVT);
    for(i=0; i < nVP; ++i)
        for(k=0; k < nVT; ++k)
            x_costs.setElement(i, k, pb_->getCost(GraphElement::VERTEX, i, k) - pb_->getQuery()->getVertex(i)->getCost() - pb_->getTarget()->getVertex(k)->getCost());
}

void GraphEditDistance::restrictProblem(double up) {
    if(up < 1) {
        for(auto row : x_variables)
            for(auto v : row)
                v->activate();

        QList<double> v;
        for(i=0; i < nVP; ++i) {
            v = x_costs.getRow(i);
            std::sort(v.begin(), v.end());
            for(k=0; k < nVT; ++k)
                if(x_costs.getElement(i, k) > v[floor(nVT * up)])
                    x_variables.getElement(i, k)->deactivate();
        }

        for(k=0; k < nVT; ++k) {
            v = x_costs.getCol(k);
            std::sort(v.begin(), v.end());
            for(i=0; i < nVP; ++i)
                if(x_costs.getElement(i, k) > v[floor(nVP * up)])
                    x_variables.getElement(i, k)->deactivate();
        }
    }
}

void GraphEditDistance::cut(Solution *sol, CutMethod cm) {
    LinearConstraint *c;
    QList<Variable *> vars = sol->getVariables().keys();
    switch(cm) {
        case SOLUTION:
            c = new LinearConstraint(LinearExpression::sum(vars), Constraint::LESS_EQ, vars.size() - 1);
            break;
        case MATCHINGS:
            c = new LinearConstraint(LinearExpression::sum(vars), Constraint::EQUAL, 0);
            break;
        case ELEMENTS:
            Exception("Element cut-strategy does not make sense for graph edit distance.");
            break;
        default:
            break;
    }
    if(lp_)
        *lp_ += c;
    else if(qp_)
        *qp_ += c;
}
