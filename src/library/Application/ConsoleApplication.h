#ifndef GEMPP_CONSOLEAPPLICATION_H
#define GEMPP_CONSOLEAPPLICATION_H

#include <QCommandLineParser>
#include <QCoreApplication>
#include "Core/Printer.h"

/**
 * @brief The ConsoleApplication class implements text-based applications,
 * defining methods for help and version showing, command line parameters
 * parsing, and error handling.
 * @author Julien Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT ConsoleApplication : public QCoreApplication {
    public:
        /**
         * @brief Constructs a new ConsoleApplication object with parameters.
         * @param argc the number of command line arguments
         * @param argv the array of command line arguments
         */
        ConsoleApplication(int &argc, char **argv);

        /**
         * @brief Destructs a ConsoleApplication object
         */
        ~ConsoleApplication();

        /**
         * @brief Sets the description of the application.
         * @param description the description
         */
        static void setApplicationDescription(const QString &description);

        /**
         * @brief Appends this description to the overall description of the application.
         * @param description the description
         */
        static void appendApplicationDescription(const QString &description);

        /**
         * @brief Returns the description of the application.
         * @return the description
         */
        static QString applicationDescription();

        /**
         * @brief Adds a positional argument to the command line arguments parser.
         * @param name the name of the argument
         * @param description the description of the argument
         * @param syntax the optional syntax description
         */
        static void addPositionalArgument(const QString &name, const QString &description = QString(), const QString &syntax = QString());

        /**
         * @brief Adds an optional argument to the command line arguments parser.
         * @param shortname the name of the short form switch (-shortname)
         * @param longname the name of the long form switch (--longname)
         * @param description the description of the option
         * @param valueName the name and/or the syntax of the option value
         * @param defaultValue the default value that will be stored in the option
         */
        static void addOption(const QString &shortname = QString(), const QString &longname = QString(), const QString &description = QString(),
                       const QString &valueName = QString(), const QString &defaultValue = QString());

        /**
         * @brief Adds a default verbose option (-v, --verbose).
         */
        static void addVerboseOption();

        /**
         * @brief Adds a default version option (--version).
         */
        static void addVersionOption();

        /**
         * @brief Adds a default help option (-h, --help).
         */
        static void addHelpOption();

        /**
         * @brief Parses the command line arguments.
         */
        static void parseArguments();

        /**
         * @brief Processes the command line arguments.
         */
        static void processArguments();

        /**
         * @brief Indicated whether an option is set
         * in the command line arguments.
         * @return a boolean
         */
        static bool isOptionSet(const QString &name);

        /**
         * @brief Returns the value of an option.
         * @return the value
         */
        static QString optionValue(const QString &name);

        /**
         * @brief Returns the list of the values of the
         * positional arguments.
         * @return the list
         */
        static QStringList positionalArguments();

        /**
         * @brief Clears the positional arguments from the
         * arguments list.
         */
        static void clearPositionalArguments();

        /**
         * @brief Displays application version and exits.
         */
        static void showVersion();

        /**
         * @brief Displays help message and exits.
         */
        static void showHelp();

        /**
         * @brief Hooks the exceptions up and tries to
         * propagate it, or show an error message and
         * exits if the exception is not caught.
         */
        virtual bool notify(QObject *o, QEvent *e);

        /**
         * @brief Displays an error message and exits.
         */
        void error(std::exception &e);

    protected:
        /**
         * @brief The command line arguments parser.
         */
        static QCommandLineParser parser_;
};

#endif /* GEMPP_CONSOLEAPPLICATION_H */
