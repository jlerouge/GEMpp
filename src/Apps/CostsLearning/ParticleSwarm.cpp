#include "ParticleSwarm.h"

ParticleSwarm::ParticleSwarm(GraphList *train, GraphList *valid, Weights *min, Weights *max, Matcher *matcher) : train_(train), valid_(valid), min_(min), max_(max), matcher_(matcher), graphsPerClass_(0), iteration_(0) {}

ParticleSwarm::~ParticleSwarm() {
    for(auto p: particles_)
        delete p;
}

void ParticleSwarm::init(int nbParticles, int graphsPerClass, double c1, double c2, double omega, double followingRatio) {
    distMatrix_ = Matrix<double>(valid_->getNbClasses()*graphsPerClass, train_->getNbClasses()*graphsPerClass);

    iteration_ = 0;
    graphsPerClass_ = graphsPerClass;
    if(!particles_.isEmpty()) {
        for(auto p: particles_)
            delete p;
    }
    particles_ = QList<Particle *>();
    c1_ = c1;
    c2_ = c2;
    omega_ = omega;

    for(int k=0; k < nbParticles; ++k) {
        Weights *w = new Weights(*min_);
        for(auto it = min_->getWeights().begin(); it != min_->getWeights().end(); ++it) {
            double p = Random::randDouble();
            w->setWeight(it.key(), p*it.value()+(1-p)*max_->getWeight(it.key()));
        }
        particles_.append(new Particle(k, w, computeFitness(w)));
    }

    int toFollow = (int)ceil((nbParticles-1)*followingRatio);
    if(toFollow >= nbParticles)
        toFollow = nbParticles-1;

    for(int k=0; k < nbParticles; ++k) {
        QVector<int> ids = Random::randPerm(0, nbParticles-1);
        ids.remove(ids.indexOf(k));
        for(int id=0; id < toFollow; ++id)
            particles_[k]->follow(particles_[ids[id]]);
    }
}

void ParticleSwarm::iterate() {
    ++iteration_;
    for(auto p : particles_) {
        p->updateVelocity(c1_, c2_, omega_);
        p->updatePosition();
        p->updateFitness(computeFitness(p->getPosition(iteration_)));
    }
}

double ParticleSwarm::computeFitness(Weights *w) {
    QSet<QString> trainClasses = train_->getClasses().toSet();
    QSet<QString> validClasses = valid_->getClasses().toSet();
    /* Verify that classes exist and that train and valid
       graphs set have exactly the same set of classes */
    if((train_->getNbClasses() > 0) && (trainClasses.intersect(validClasses).size() == train_->getNbClasses())) {
        QList<Graph *> subtrain, subvalid;
        QVector<int> tperm, vperm;

        for(int c=0; c < train_->getNbClasses(); ++c) {
            QString graphClass = train_->getClasses().at(c);
            tperm = Random::randPerm(0, train_->getClassSize(graphClass)-1);
            vperm = Random::randPerm(0, train_->getClassSize(graphClass)-1);
            for(int k=0; k < graphsPerClass_; ++k) {
                subtrain.append(train_->getGraph(graphClass, tperm[k]));
                subvalid.append(valid_->getGraph(graphClass, vperm[k]));
            }
        }

        // Begin solve loop
        for(int v = 0; v < subvalid.size(); ++v) {
            for(int t = 0; t < subtrain.size(); ++t) {
                Problem *pb = new Problem(Problem::GED, subvalid[v], subtrain[t], w);
                matcher_->setProblem(pb);
                distMatrix_.setElement(v, t, matcher_->run());
                delete pb;
            }
        }
        // End loop

        return knnScore(5); // FIXME (?)
    } else {
        throw std::logic_error("ParticleSwarm can't compute classification score as the classes of the train and valid graph sets are inconsistent or inexistant.");
    }
    return 0;
}

void ParticleSwarm::print(Printer *p) {
    p->dump("ParticleSwarm {");
    p->indent();
    p->dump(QString("iterations : %1").arg(iteration_));
    p->dump("particles {");
    p->indent();
    for(auto part: particles_)
        part->print(p);
    p->unindent();
    p->dump("}");
    p->unindent();
    p->dump("}");
}

double ParticleSwarm::knnScore(int k) {
    QVector<int> classGuess;
    QList<double> dist;
    int guess, nn;
    int correct = 0;

    for(int v = 0; v < distMatrix_.getNbRows(); ++v) {
        classGuess = QVector<int>(train_->getNbClasses(), 0);
        dist = distMatrix_.getRow(v);
        sort(dist.begin(), dist.end());
        for(int c=0; c < k; ++c) {
            nn = distMatrix_.getRow(v).indexOf(dist[c]);
            distMatrix_.setElement(v, nn, INFINITY); // do not count the same element several times
            classGuess[nn/graphsPerClass_] += 1;
        }
        guess = -1;
        nn = -1;
        for(int c=0; c < classGuess.size(); ++c) {
            if(classGuess[c] > guess) {
                guess = classGuess[c];
                nn = c;
            }
        }
        correct += (nn == (v/graphsPerClass_));
    }

    return correct/(double)distMatrix_.getNbRows();
}

void ParticleSwarm::save(const QString &filename) {
    FileStream::saveFile(this, filename);
}
