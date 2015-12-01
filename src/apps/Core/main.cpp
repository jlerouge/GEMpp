#include "Application/ApplicationFactory.h"

int main(int argc, char **argv) {
    ConsoleApplication coreApp(argc, argv);
    coreApp.setApplicationDescription("GEM++ command line interface gives access to the commands of the GEM++ framework.");
    coreApp.addHelpOption();
    coreApp.addVersionOption();
    coreApp.addPositionalArgument("command", "A GEM++ command (dist, sub, multidist, multisub, GUI)", "command");

    try {
        // Retrieve arguments
        coreApp.parseArguments();

        // Show version when asked
        if(coreApp.isOptionSet("version"))
            coreApp.showVersion();

        // Recognize the command
        QStringList args = coreApp.positionalArguments();

        if(args.empty()) {
            if(coreApp.isOptionSet("help"))
                coreApp.showHelp();
            Exception("You must provide a GEM++ command.");
        }
        QString commandName = args[0];
        if(!commandName.compare("GUI", Qt::CaseInsensitive))
            return system("GEM++GUI");

        bool isMultiMatching = commandName.contains("multi", Qt::CaseInsensitive);
        if(isMultiMatching)
            commandName = commandName.replace("multi", "");
        Problem::Type type = Problem::fromName(commandName);
        commandName = Problem::toName(type).toLower();
        coreApp.clearPositionalArguments();

        // Build the new command line arguments
        int n_argc = argc-1;
        char **n_argv = (char **) malloc(n_argc*sizeof(char *));
        // Allocates memory to print the executable name and the command name
        int ret = asprintf(&n_argv[0], "%s %s", argv[0], commandName.toStdString().c_str());
        if(ret < 0)
            Exception("There was a problem with dynamic memory allocation.");
        for(int i=1; i < n_argc; ++i)
            n_argv[i] = argv[(i >= commandIndex)? i+1 : i];

        // Explicitly calls the command
        MatchingApplication *actualApp = ApplicationFactory::createApplication(n_argc, n_argv, type, isMultiMatching);
        actualApp->match();
        delete actualApp;

        // Free allocated memory for command line arguments
        free(n_argv[0]);
        free(n_argv);

    } catch (std::exception &e) {
        coreApp.error(e);
    }

    // Exit
    return EXIT_SUCCESS;
}
