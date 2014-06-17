#include <QApplication>
#include <QtPlugin>
#include "MainWindow.h"
#include "Core/Random.h"
#include "Application/GUIApplication.h"

int main(int argc, char *argv[])
{
    GUIApplication app(argc, argv);
    app.setOrganizationName("LITIS");
    app.setApplicationName("GEM++gui");
    app.setApplicationDescription("<b>GEM++gui</b> is a front-end for GEM++,<br/>"
                                  "a Graph Extraction and Matching C++ toolkit.<br/><br/>"
                                  "Julien Lerouge <a href=\"http://www.litislab.fr\">www.litislab.fr</a>");

#if defined(LINUX) // Linux style
    app.setStyle("gtk+");
#endif

    QSplashScreen screen;
    screen.setPixmap(QPixmap(":/images/splashscreen.png"));
    screen.show();
    screen.showMessage(QString("Loading..."), Qt::AlignBottom + Qt::AlignRight, Qt::red);
    QThread::sleep(1);
    app.processEvents();

    Random::seedRand();
    MainWindow w;
    w.show();
    screen.finish(&w);

    return app.exec();
}
