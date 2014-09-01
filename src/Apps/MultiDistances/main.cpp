#include "Application/MatchingApplication.h"

int main(int argc, char **argv)
{
    MatchingApplication app(argc, argv, Problem::GED, true);
    app.setOrganizationName("LITIS");
    app.setApplicationName("GEM++multidist");
    app.setApplicationDescription("\n-- Multi Graph Edit Distances (GEM++) --\n"
                                  "A graph edit distance implementation using binary programming, that\n"
                                  "finds the optimal edit path that matches a graph to another graph.\n"
                                  "There are three available formulations (option -f) :\n"
                                  "  * l(inear)    -> exact GED using binary linear programming;\n"
                                  "  * q(uadratic) -> exact GED using binary quadratic programming;\n"
                                  "  * b(ipartite) -> approximate GED using bipartite graph matching.\n"
                                  "If multiple solutions are searched ('-n' option), one of the two\n"
                                  "available cut strategies must be chosen with the '--cut' option:\n"
                                  "  * s(olution) : cuts exactly the present optimal solution (default);\n"
                                  "  * m(atching) : prevent further solutions from matching pairs\n"
                                  "                 of vertices that were already matched.\n"
                                  "\nThis application works on multiple graphs, and you may output all\n"
                                  "best objective values (-m option) and matching solutions (-O option).\n"
                                  "\nAuthor  : Julien Lerouge (LITIS EA 4108)\n"
                                  "Contact : julien.lerouge@litislab.fr\n"
                                  "Version : " + app.applicationVersion());

    app.addPositionalArgument("dir1", "Directory containing graphs", "dir1");
    app.addPositionalArgument("dir2", "Directory containing other graphs", "dir2");
    return app.match();
}

