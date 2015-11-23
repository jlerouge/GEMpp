#include "Application/MatchingApplication.h"

int main(int argc, char **argv)
{
    MatchingApplication app(argc, argv, Problem::GED);
    app.setOrganizationName("LITIS");
    app.setApplicationName("GEM++dist");
    app.setApplicationDescription("\n-- Graph Edit Distance (GEM++) --\n"
                                  "A graph edit distance implementation using binary programming, that\n"
                                  "finds the optimal edit path that matches a graph to another graph.\n"
                                  "There are three available formulations (option -f) :\n"
                                  "  * l(inear)    -> exact GED using binary linear programming;\n"
                                  "  * b(ipartite) -> approximate GED using bipartite graph matching.\n"
                                  "If multiple solutions are searched ('-n' option), one of the two\n"
                                  "available cut strategies must be chosen with the '--cut' option:\n"
                                  "  * s(olution) : cuts exactly the present optimal solution (default);\n"
                                  "  * m(atching) : prevent further solutions from matching pairs\n"
                                  "                 of vertices that were already matched.\n"
                                  "\nAuthor  : Julien Lerouge (LITIS EA 4108)\n"
                                  "Contact : julien.lerouge@litislab.fr\n"
                                  "Version : " + app.applicationVersion());
    app.addPositionalArgument("graph1.gml/.gxl", "A directed or undirected graph", "graph1");
    app.addPositionalArgument("graph2.gml/.gxl", "Another graph of the same type", "graph2");
    return app.match();
}
