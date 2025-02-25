#include "ConsoleApplication.h"

QCommandLineParser ConsoleApplication::parser_;

ConsoleApplication::ConsoleApplication(int &argc, char **argv) : QCoreApplication(argc, argv) {
    setApplicationVersion(QString("%1 (build : %2 @ %3)").arg(GEMPP_VERSION, __DATE__, __TIME__));
    setOrganizationName(ORGANIZATION_NAME);
    setApplicationName(APPLICATION_NAME);
}

ConsoleApplication::~ConsoleApplication() {}

void ConsoleApplication::setApplicationDescription(const QString &description) {
    parser_.setApplicationDescription(description);
}

void ConsoleApplication::appendApplicationDescription(const QString &description) {
    parser_.setApplicationDescription(parser_.applicationDescription() + description);
}

QString ConsoleApplication::applicationDescription() {
    return parser_.applicationDescription();
}

void ConsoleApplication::addPositionalArgument(const QString &name, const QString &description, const QString &syntax) {
    parser_.addPositionalArgument(name, description, syntax);
}

void ConsoleApplication::addOption(const QString &shortname, const QString &longname, const QString &description,
                                   const QString &valueName, const QString &defaultValue) {
    QStringList sl;
    if(!shortname.isEmpty())
        sl << shortname;
    if(!longname.isEmpty())
        sl << longname;
    if(sl.isEmpty())
        Exception("At least one name (short or long) must be given to an option.");
    QCommandLineOption opt = QCommandLineOption(sl, description, valueName, defaultValue);
    parser_.addOption(opt);
}

void ConsoleApplication::addHelpOption() {
    parser_.addHelpOption();
}

void ConsoleApplication::addVersionOption() {
    addOption(QString(), "version", "Displays the application version.");
}

void ConsoleApplication::addVerboseOption() {
    addOption("v", "verbose", "Shows additional information.");
}

void ConsoleApplication::parseArguments() {
    parser_.parse(instance()->arguments());
}

void ConsoleApplication::processArguments() {
    parser_.process(instance()->arguments());
}

bool ConsoleApplication::isOptionSet(const QString &name) {
    return parser_.isSet(name);
}

QString ConsoleApplication::optionValue(const QString &name) {
    return parser_.value(name);
}

QStringList ConsoleApplication::positionalArguments() {
    return parser_.positionalArguments();
}

void ConsoleApplication::clearPositionalArguments() {
    parser_.clearPositionalArguments();
}

void ConsoleApplication::showVersion() {
    qcout << ConsoleApplication::applicationName() << " " << ConsoleApplication::applicationVersion() << endl;
    ::exit(EXIT_SUCCESS);
}

void ConsoleApplication::showHelp() {
    parser_.showHelp(EXIT_SUCCESS);
}

bool ConsoleApplication::notify(QObject *o, QEvent *e) {
    try {
        return QCoreApplication::notify(o, e);
    } catch (std::exception &ex) {
        error(ex);
    }
    return false;
}

void ConsoleApplication::error(std::exception &e) {
    qcerr << e.what() << endl;
    qcerr << QString("Run '%1 -h' for help.").arg(applicationName()) << endl;
    ::exit(EXIT_FAILURE);
}
