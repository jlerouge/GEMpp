#include "GUIApplication.h"

QString GUIApplication::applicationDescription_;

GUIApplication::GUIApplication(int &argc, char **argv) : QApplication(argc, argv) {
    setOrganizationName(ORGANIZATION_NAME);
    setApplicationName(APPLICATION_NAME);
}

GUIApplication::~GUIApplication() {}

void GUIApplication::setApplicationDescription(const QString &description) {
    applicationDescription_ = description;
}

QString GUIApplication::applicationDescription() {
    return applicationDescription_;
}

GUIApplication *GUIApplication::instance() {
    return dynamic_cast<GUIApplication *>(QCoreApplication::instance());
}

bool GUIApplication::notify(QObject *o, QEvent *e) {
    try {
      return QApplication::notify(o, e);
    } catch (std::exception &ex) {
        error(ex);
    }
    return false;
}

void GUIApplication::error(std::exception &e) {
    QMessageBox::warning(0, "Warning", e.what(), "OK");
}

void GUIApplication::about() {
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("About "+applicationName());
    aboutBox.setText(applicationDescription());
    aboutBox.setIconPixmap(QPixmap(":/images/about.png"));
    aboutBox.exec();
}

void GUIApplication::aboutQt() {
    QMessageBox::aboutQt(0);
}
