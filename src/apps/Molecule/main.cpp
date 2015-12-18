#include "Application/ApplicationFactory.h"
#include "Hierarchizer.h"

int main(int argc, char **argv) {
    ConsoleApplication coreApp(argc, argv);
    coreApp.setApplicationDescription("GEM++molecule [coming description]");
    coreApp.addHelpOption();
    coreApp.addVersionOption();
    coreApp.addPositionalArgument("graph.[gml|gxl|xml]", "A molecule graph filename", "graph");
    coreApp.addPositionalArgument("output.gxl", "An output graph filename", "output");

    try {
        // Retrieve arguments
        coreApp.parseArguments();

        // Show version or help when asked
        if(coreApp.isOptionSet("version"))
            coreApp.showVersion();
        if(coreApp.isOptionSet("help"))
            coreApp.showHelp();

        // Get the graph filename
        QStringList args = coreApp.positionalArguments();
        if(args.empty())
            Exception("You must provide a graph file.");
        QString graphFilename = args[0];
        Graph *graph = new Graph(graphFilename);

        //graph->save(FileUtils::changeExtension(graphFilename, "copy.gml"));
        Hierarchizer *hierarchizer = new Hierarchizer(graph);
        hierarchizer->extract();

        QString output = FileUtils::changeExtension(graphFilename, "hierarchical.gxl");
        if(args.size() > 1)
            output = args[1];
        hierarchizer->getOutput()->save(output);

    } catch (std::exception &e) {
        coreApp.error(e);
    }
    // Exit
    return EXIT_SUCCESS;
}
