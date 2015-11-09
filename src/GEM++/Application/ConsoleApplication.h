#ifndef GEMPP_CONSOLEAPPLICATION_H
#define GEMPP_CONSOLEAPPLICATION_H

#include <QCommandLineParser>
#include <QCoreApplication>
#include "../Core/Printer.h"

class DLL_EXPORT ConsoleApplication : public QCoreApplication {
    public:
        ConsoleApplication(int &argc, char **argv);
        ~ConsoleApplication();

        static void setApplicationDescription(const QString &description);
        static QString applicationDescription();
        static void addPositionalArgument(const QString &name, const QString &description = QString(), const QString &syntax = QString());
        static void addOption(const QString &shortname = QString(), const QString &longname = QString(), const QString &description = QString(),
                       const QString &valueName = QString(), const QString &defaultValue = QString());

        static void addVerboseOption();
        static void addVersionOption();
        static void addHelpOption();
        static void processArguments();
        static bool isOptionSet(const QString &name);
        static QString optionValue(const QString &name);
        static QStringList positionalArguments();

        static void showVersion();
        virtual bool notify(QObject *o, QEvent *e);
        void error(std::exception &e);

    protected:
        static QCommandLineParser parser_;
};

#endif /* GEMPP_CONSOLEAPPLICATION_H */
