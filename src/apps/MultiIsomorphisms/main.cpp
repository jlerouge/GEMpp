#include "Application/MatchingApplication.h"

int main(int argc, char **argv)
{
    MatchingApplication app(argc, argv, Problem::SUBGRAPH, true);
    app.setOrganizationName("LITIS");
    app.setApplicationName("GEM++multisub");
    app.setApplicationDescription("\n-- Multi Subgraph Isomorphisms (GEM++) --\n"
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
                                     "\nThis application works on multiple query and target graphs, and you may\n"
                                     "output all best objective values (-m option) and matching solutions (-O option).\n"
                                     "\nAuthor  : Julien Lerouge (LITIS EA 4108)\n"
                                     "Contact : julien.lerouge@litislab.fr\n"
                                     "Version : " + app.applicationVersion());
    app.addPositionalArgument("queries", "Directory containing query graphs", "queries");
    app.addPositionalArgument("targets", "Directory containing target graphs", "targets");
    return app.match();
}

