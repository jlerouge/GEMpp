#include "ApplicationFactory.h"

MatchingApplication *ApplicationFactory::createApplication(int &argc, char **argv, Problem::Type type, bool isMultiMatching) {
    MatchingApplication *app = new MatchingApplication(argc, argv, type, isMultiMatching);

    app->setApplicationDescription(QString("\n-- %1 : %2%3 --\n").arg(APPLICATION_NAME, Problem::toName(type), (isMultiMatching?"s":"")));

    switch(type) {
        case Problem::GED:
            app->appendApplicationDescription("A graph edit distance implementation using binary programming, that\n"
                                              "finds the optimal edit path that matches a graph to another graph.\n"
                                              "There are two available formulations (option -f) :\n"
                                              "  * l(inear)    -> exact GED using binary linear programming;\n"
                                              "  * b(ipartite) -> approximate GED using bipartite graph matching.\n"
                                              "If multiple solutions are searched ('-n' option), one of the two\n"
                                              "available cut strategies must be chosen with the '--cut' option:\n"
                                              "  * s(olution) : cuts exactly the present optimal solution (default);\n"
                                              "  * m(atching) : prevent further solutions from matching pairs\n"
                                              "                 of vertices that were already matched.\n");
            if(isMultiMatching) {
                app->addPositionalArgument("dir1", "Directory containing graphs", "dir1");
                app->addPositionalArgument("dir2", "Directory containing other graphs", "dir2");
            } else {
                app->addPositionalArgument("graph1.[gml|gxl|xml]", "A directed or undirected graph", "graph1");
                app->addPositionalArgument("graph2.[gml|gxl|xml]", "Another graph of the same type", "graph2");
            }
            break;
        case Problem::SUBGRAPH:
            app->appendApplicationDescription("A subgraph matching implementation using binary linear programming,\n"
                                             "that attempts to find the subgraph of the target that best matches the\n"
                                             "query graph. There are three levels of tolerance (-t option):\n"
                                             "  * e(xact)    -> not tolerant (perfect matching);\n"
                                             "  * l(abel)    -> tolerant to label errors;\n"
                                             "  * t(opology) -> tolerant to label and topology errors (default).\n");

            if(isMultiMatching) {
                app->addPositionalArgument("queries", "Directory containing query graphs", "queries");
                app->addPositionalArgument("targets", "Directory containing target graphs", "targets");
            } else {
                app->addPositionalArgument("query.[gml|gxl|xml]", "A directed or undirected query graph", "query");
                app->addPositionalArgument("target.[gml|gxl|xml]", "A graph of the same type", "target");
            }
            break;
        default:
            break;
    }

    app->appendApplicationDescription("If multiple solutions are searched ('-n' option), one of the three\n"
                                      "available cut strategies must be chosen with the '--cut' option:\n"
                                      "  * s(olution) : cuts exactly the present optimal solution (default);\n"
                                      "  * m(atching) : prevent further solutions from matching pairs\n"
                                      "                 of vertices that were already matched.\n"
                                      "  * e(lements) : prevent further solutions from matching vertices\n"
                                      "                 that were already matched with any other vertex.\n");
    if(isMultiMatching)
        app->appendApplicationDescription("\nThis application works on multiple graphs, and you may output all\n"
                                          "best objective values (-m option) and matching solutions (-O option).\n");
    app->appendApplicationDescription(QString("Contact : %1\nVersion : %2").arg(CONTACT_EMAIL, app->applicationVersion()));
    return app;
}
