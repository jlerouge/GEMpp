#include "Particle.h"

Particle::Particle(int id, Weights *position, double fitness) : id_(id) {
    positions_ = QVector<Weights *>();
    positions_.push_back(position);
    fitnesses_ = QVector<double>();
    fitnesses_.push_back(fitness);
    bestIter_ = 0;

    followed_ = QVector<Particle *>();
    velocity_ = new Weights(*position);
    *velocity_ *= 0;
}

Particle::~Particle() {
    for(auto w: positions_)
        delete w;
}

Weights *Particle::getInitPosition() {
    return positions_[0];
}

double Particle::getInitFitness() {
    return fitnesses_[0];
}

Weights *Particle::getPosition(int iter) {
    return positions_[iter];
}

double Particle::getFitness(int iter) {
    return fitnesses_[iter];
}

Weights *Particle::getBestPosition() {
    return positions_[bestIter_];
}

double Particle::getBestFitness() {
    return fitnesses_[bestIter_];
}

void Particle::setID(int id) {
    id_ = id;
}

int Particle::getID() {
    return id_;
}

void Particle::follow(Particle *p) {
    followed_.push_back(p);
}

void Particle::updateVelocity(double c1, double c2, double omega) {
    Weights w;
    double r1 = Random::randDouble();
    double r2 = Random::randDouble();
    *velocity_ *= omega;
    w = Weights(*getBestPosition());
    w *= (c1*r1);
    *velocity_ += w;
    w = Weights(*getGuide());
    w *= (c2*r2);
    *velocity_ += w;
    w = Weights(*(positions_.last()));
    w *= (-c1*r1-c2*r2);
    *velocity_ += w;
}

void Particle::updatePosition() {
    Weights *w = new Weights(*(positions_.last())); // copy constructor
    *w += *velocity_;
    positions_.push_back(w);
}

void Particle::updateFitness(double fitness) {
    fitnesses_.push_back(fitness);
    // This should never happen
    if(fitnesses_.size() != positions_.size())
        throw std::logic_error(QString("Fitness and position of particle %1 were not consistent during iteration %2.").arg(id_).arg(positions_.size()-1).toStdString());

    if(fitness >= getBestFitness())
        bestIter_ = fitnesses_.size() - 1; // current iteration is the best
}

void Particle::print(Printer *p) {
    QHash<QString, double> w;
    p->dump(QString("Particle %1 {").arg(id_));
    p->indent();
    p->dump("followed {");
    p->indent();
    for(auto f: followed_)
        p->dump(QString::number(f->getID()));
    p->unindent();
    p->dump("}");
    for(int i=0; i < positions_.size(); ++i) {
        p->dump(QString("iteration %1 {").arg(i));
        p->indent();
        p->dump("position {");
        p->indent();
        w = positions_[i]->getWeights();
        for(auto it = w.begin(); it != w.end(); ++it) {
            p->dump(QString("%1 : %2").arg(it.key()).arg(it.value()));
        }
        p->unindent();
        p->dump("}");
        p->dump(QString("fitness : %1").arg(fitnesses_[i]));
        p->unindent();
        p->dump("}");
    }
    p->unindent();
    p->dump("}");
}

void Particle::save(const QString &filename) {
    FileStream::saveFile(this, filename);
}

Weights *Particle::getGuide() {
    double maxFit = 0.0;
    int guide = 0;
    for(int k=0; k < followed_.size(); ++k) {
        if(followed_[k]->getBestFitness() > maxFit) {
            maxFit = followed_[k]->getBestFitness();
            guide = k;
        }
    }
    return followed_[guide]->getBestPosition();
}
