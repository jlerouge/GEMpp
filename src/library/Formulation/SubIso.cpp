#include "SubIso.h"

const char *SubgraphIsomorphism::methodName[SubgraphIsomorphism::COUNT] = {
    "Exact",
    "Label",
    "Topology"
};

SubgraphIsomorphism::Method SubgraphIsomorphism::fromName(QString name) {
    for(Method m = (Method)0; m < COUNT; m = (Method)((int)m + 1))
        if(QString(methodName[m]).startsWith(name, Qt::CaseInsensitive))
            return m;
    Exception(QString("Method '%1' not recognized, please use e(xact), l(abel), or t(opology).").arg(name));
    return COUNT;
}

QString SubgraphIsomorphism::toName(Method method) {
    return methodName[method];
}

SubgraphIsomorphism::~SubgraphIsomorphism() {
    for(auto v : x_variables)
        for(auto it : v)
            delete it;
    for(auto v : y_variables)
        for(auto it : v)
            delete it;
}

void SubgraphIsomorphism::initVariables() {
    QString id;
    x_variables = Matrix<Variable*>(nVP, nVT);
    for(i=0; i < nVP; ++i) {
        for(k=0; k < nVT; ++k) {
            //id = QString("x_%1,%2").arg(pb_->getPattern()->getVertex(i)->getIndex()).arg(pb_->getTarget()->getVertex(k)->getIndex());
            id = QString("x_%1,%2").arg(i).arg(k);
            x_variables.setElement(i, k, new Variable(id));
        }
    }
    y_variables = Matrix<Variable*>(nEP, nET);
    for(ij=0; ij < nEP; ++ij) {
        for(kl=0; kl < nET; ++kl) {
            //id = QString("y_%1,%2").arg(pb_->getPattern()->getEdge(ij)->getIndex()).arg(pb_->getTarget()->getEdge(kl)->getIndex());
            id = QString("y_%1,%2").arg(ij).arg(kl);
            y_variables.setElement(ij, kl, new Variable(id));
        }
    }
}

void SubgraphIsomorphism::initCosts() {
    x_costs = Matrix<double>(nVP, nVT);
    for(i=0; i < nVP; ++i)
        for(k=0; k < nVT; ++k)
            x_costs.setElement(i, k, pb_->getCost(i, k, GraphElement::VERTEX));
    y_costs = Matrix<double>(nEP, nET);
    for(ij=0; ij < nEP; ++ij)
        for(kl=0; kl < nET; ++kl)
            y_costs.setElement(ij, kl, pb_->getCost(ij, kl, GraphElement::EDGE));
}

void SubgraphIsomorphism::initObjective() {
    LinearExpression *exp = new LinearExpression();
    for(i=0; i < nVP; ++i)
        for(k=0; k < nVT; ++k)
            *exp += *x_variables.getElement(i, k)*x_costs.getElement(i, k);

    for(ij=0; ij < nEP; ++ij)
        for(kl=0; kl < nET; ++kl)
            *exp += *y_variables.getElement(ij, kl)*y_costs.getElement(ij, kl);

    lp_->setObjective(exp);
}

void SubgraphIsomorphism::cut(Solution *sol, CutMethod cm) {
    LinearConstraint *c;
    QList<Variable *> vars = sol->getVariables().keys();
    switch(cm) {
        case SOLUTION:
            c = new LinearConstraint(LinearExpression::sum(vars), Constraint::LESS_EQ, vars.size() - 1);
            break;
        case MATCHINGS:
            c = new LinearConstraint(LinearExpression::sum(vars), Constraint::EQUAL, 0);
            break;
        case ELEMENTS: {
            QStringList sl;
            QSet<Variable *> vset = vars.toSet();
            for(auto s : vars) {
                if(s->getID().startsWith("x")) {
                    sl = s->getID().mid(2).split(',');
                    for(auto v : x_variables.getCol(sl[1].toInt())) {
                        vset.insert(v);
                    }
                }
            }
            c = new LinearConstraint(LinearExpression::sum(vset.toList()), Constraint::EQUAL, 0);
            break;
        }
        default:
            break;
    }
    *lp_ += c;
}
