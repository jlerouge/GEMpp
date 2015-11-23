#ifndef __PARTICLESWARM_H__
#define __PARTICLESWARM_H__

#include "Particle.h"
#include "Solver/Matcher.h"
#include "Model/GraphList.h"

class GEM_DLLSPEC ParticleSwarm : virtual public IPrintable, virtual public ISaveable {
    public:
        ParticleSwarm(GraphList *train, GraphList *valid, Weights *min, Weights *max, Matcher *matcher);
        ~ParticleSwarm ();

        void init(int nbParticles, int graphsPerClass, double c1, double c2, double omega, double followingRatio);
        double computeFitness(Weights *w);
        void iterate();

        void print(Printer *p);
        void save(const QString &filename);

    private:
        QList<Particle *> particles_;
        GraphList* train_;
        GraphList* valid_;
        Weights *min_;
        Weights *max_;
        Matcher *matcher_;
        double c1_;
        double c2_;
        double omega_;
        int graphsPerClass_;
        int iteration_;

        Matrix<double> distMatrix_;

        double knnScore(int k);
};

#endif /* __PARTICLESWARM_H__ */
