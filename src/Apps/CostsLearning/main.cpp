#include <QCommandLineParser>
#include <QtWidgets/QtWidgets>
#include "Core/Random.h"
#include "Model/GraphList.h"
#include "Model/Problem.h"
#include "Solver/Matcher.h"
#include "ParticleSwarm.h"

int error(const QString &message) {
    qcerr << message << endl;
    qcerr << "Run 'GEM++learn -h' for help." << endl;
    return EXIT_FAILURE;
}

int showVersion() {
    qcout << QCoreApplication::applicationName() << endl;
    qcout << QCoreApplication::applicationVersion() << endl;
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("Costs Learning (GEM++)");
    QString version = QString("%1 (build : %2 @ %3)").arg(VERSION, __DATE__, __TIME__);
    QCoreApplication::setApplicationVersion(version);

    QCommandLineParser parser;
    parser.setApplicationDescription("\n -- " + QCoreApplication::applicationName() + " --\nAuthor  : Julien Lerouge (LITIS EA 4108)\nContact : julien.lerouge@litislab.fr\nVersion : " + QCoreApplication::applicationVersion());
    parser.addPositionalArgument("train", "A directory containing training graphs", "train");
    parser.addPositionalArgument("valid", "A directory containing validation graphs", "valid");

    QCommandLineOption optSubstitutionMin = QCommandLineOption(QStringList() << "smin", "Defines the min weights for substitution", "smin.fw");
    parser.addOption(optSubstitutionMin);
    QCommandLineOption optSubstitutionMax = QCommandLineOption(QStringList() << "smax", "Defines the max weights for substitution", "smax.fw");
    parser.addOption(optSubstitutionMax);
    QCommandLineOption optCreationMin = QCommandLineOption(QStringList() << "cmin", "Defines the min weights for creation", "cmin.fw");
    parser.addOption(optCreationMin);
    QCommandLineOption optCreationMax = QCommandLineOption(QStringList() << "cmax", "Defines the max weights for creation", "cmax.fw");
    parser.addOption(optCreationMax);
    QCommandLineOption optFormulation = QCommandLineOption(QStringList() << "f" << "formulation", "Sets the formulation type (default : l)", "l/q/b");
    parser.addOption(optFormulation);
    QCommandLineOption optAggregation = QCommandLineOption(QStringList() << "a" << "aggregation", "Lower bound approx. (rows aggregation)");
    parser.addOption(optAggregation);
    QCommandLineOption optRowGen = QCommandLineOption(QStringList() << "r" << "row-gen", "Uses (iterative) row generation (forces -a)");
    parser.addOption(optRowGen);
    QCommandLineOption optExploration = QCommandLineOption(QStringList() << "e" << "explore", "Upper bound approx. (matchings limit)", "0 - 100%");
    parser.addOption(optExploration);
    QCommandLineOption optColGen = QCommandLineOption(QStringList() << "k" << "col-gen", "Sets the step to use column generation", "0 - 100%");
    parser.addOption(optColGen);
    QCommandLineOption optVerbose = QCommandLineOption(QStringList() << "v" << "verbose", "Shows additional information (solver log)");
    parser.addOption(optVerbose);
    QCommandLineOption optSolver = QCommandLineOption(QStringList()  << "solver", "Sets the solver (default : Gurobi)", "Cplex/GLPK/Gurobi");
    parser.addOption(optSolver);
    QCommandLineOption optExtension = QCommandLineOption(QStringList()  << "ext", "Restricts the graph extension", ".gxl/.gml");
    parser.addOption(optExtension);
    QCommandLineOption optVersion = QCommandLineOption(QStringList()  << "version", "Shows the application version and exits");
    parser.addOption(optVersion);
    parser.addHelpOption();

    parser.process(app);

    if(parser.isSet(optVersion))
        return showVersion();

    const QStringList args = parser.positionalArguments();
    // Check number of arguments
    if(args.size() != 2)
        return error(QString("You must provide exactly 2 directories (%1 given)").arg(args.size()));

    try {
        // Initialize randomness
        Random::seedRand();

        QString ext = parser.isSet(optExtension) ? parser.value(optExtension) : "";
        // Loading all graphs
        GraphList *train = new GraphList(QDir(args.at(0)), ext);
        GraphList *valid = new GraphList(QDir(args.at(1)), ext);

        // Loading weights
        QString smin = parser.isSet(optSubstitutionMin) ? parser.value(optSubstitutionMin) : "";
        QString smax = parser.isSet(optSubstitutionMax) ? parser.value(optSubstitutionMax) : "";
        QString cmin = parser.isSet(optCreationMin) ? parser.value(optCreationMin) : "";
        QString cmax = parser.isSet(optCreationMax) ? parser.value(optCreationMax) : "";
        Weights *wmin = new Weights(smin, cmin);
        Weights *wmax = new Weights(smax, cmax);

        // Configuration of the matching
        Configuration *cfg = new Configuration();

        cfg->matrix = true;
        cfg->verbose = parser.isSet(optVerbose);
        if(parser.isSet(optFormulation))
            cfg->gedMethod = GraphEditDistance::methodFromName(parser.value(optFormulation).toLower());

        cfg->rowgen = parser.isSet(optRowGen);
        cfg->lowerbound = parser.isSet(optAggregation) || cfg->rowgen;

        cfg->upperbound = parser.isSet(optExploration);
        if(cfg->upperbound)
            cfg->limit = parser.value(optExploration).toDouble()/100;

        cfg->colgen = parser.isSet(optColGen);
        if(cfg->colgen)
            cfg->step = parser.value(optColGen).toDouble()/100;

        if(parser.isSet(optSolver))
            cfg->solver = parser.value(optSolver);

        // Initiliaze the matcher
        Matcher *matcher = new Matcher();
        matcher->configure(cfg);


        // TODO : a config file for the PSO
        ParticleSwarm* pso = new ParticleSwarm(train, valid, wmin, wmax, matcher);

        // Iteration 0
        int tbegin = time(NULL);
        pso->init(20, 10, 0.25, 0.25, 0.95, 0.5);

        Printer p;
        pso->print(&p);
        p.show();
        p.reset();
        qcout << QString("time : %1 sec").arg(time(NULL)-tbegin) << endl;

        // Begin optimization loop
        for(int iter=0; iter < 50; ++iter) {
            pso->iterate();
            pso->print(&p);
            p.show();
            p.reset();
            qcout << QString("time : %1 sec").arg(time(NULL)-tbegin) << endl;
        }
        // End loop

        delete pso;
        delete train;
        delete valid;
        delete cfg;
        delete matcher;
    } catch (const std::logic_error &e) {
        return error(QString(e.what()));
    }

    // Exit
    return EXIT_SUCCESS;
}

