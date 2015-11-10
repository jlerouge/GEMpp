#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <QVector>
#include "Core/Random.h"
#include "Core/IPrintable.h"
#include "Core/ISaveable.h"
#include "Model/Weights.h"

class GEM_DLLSPEC Particle : virtual public IPrintable, virtual public ISaveable {
    public:
        Particle(int id, Weights *position, double fitness);
        ~Particle();

        Weights *getInitPosition();
        double getInitFitness();
        Weights *getPosition(int iter);
        double getFitness(int iter);
        Weights *getBestPosition();
        double getBestFitness();
        void setID(int id);
        int getID();

        void follow(Particle *p);

        void updateVelocity(double c1, double c2, double omega);
        void updatePosition();
        void updateFitness(double fitness);

        void print(Printer *p);
        void save(const QString &filename);

    private:
        Weights *getGuide();

        int id_;
        Weights *velocity_;
        QVector<Weights *> positions_;
        QVector<double> fitnesses_;
        QVector<Particle *> followed_;
        int bestIter_;
};

#endif /* __MATCHER_H__ */
