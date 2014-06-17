#include "Application/MatchingApplication.h"

int main(int argc, char **argv)
{
    MatchingApplication app(argc, argv, Problem::SUBGRAPH);
    app.setOrganizationName("LITIS");
    app.setApplicationName("GEM++sub");
    app.setApplicationDescription("\n-- Subgraph Isomorphism (GEM++) --\n"
                                  "A subgraph isomorphism implementation using binary linear programming,\n"
                                  "that attempts to find the subgraph of the target that best matches the\n"
                                  "query graph. There are three levels of tolerance (-t option):\n"
                                  "  * e(xact)    -> not tolerant (perfect matching);\n"
                                  "  * l(abel)    -> tolerant to label errors;\n"
                                  "  * t(opology) -> tolerant to label and topology errors (default).\n"
                                  "If multiple solutions are searched ('-n' option), one of the three\n"
                                  "available cut strategies must be chosen with the '--cut' option:\n"
                                  "  * s(olution) : cuts exactly the present optimal solution (default);\n"
                                  "  * m(atching) : prevent further solutions from matching pairs\n"
                                  "                 of vertices that were already matched.\n"
                                  "  * e(lements) : prevent further solutions from matching vertices\n"
                                  "                 that were already matched with any other vertex.\n"
                                  "\nAuthor  : Julien Lerouge (LITIS EA 4108)\n"
                                  "Contact : julien.lerouge@litislab.fr\n"
                                  "Version : " + app.applicationVersion());

    app.addPositionalArgument("query.gml/.gxl", "A directed or undirected query graph", "query");
    app.addPositionalArgument("target.gml/.gxl", "A graph of the same type", "target");
    return app.match();
}
