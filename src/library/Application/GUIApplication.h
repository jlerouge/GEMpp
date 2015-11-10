#ifndef GEMPP_GUIAPPLICATION_H
#define GEMPP_GUIAPPLICATION_H

#include <QMessageBox>
#include <QApplication>
#include "Core/Portability.h"

class DLL_EXPORT GUIApplication : public QApplication {
        Q_OBJECT
    public:
        GUIApplication(int &argc, char **argv);
        ~GUIApplication();

        static void setApplicationDescription(const QString &description);
        static QString applicationDescription();
        static GUIApplication *instance();

        virtual bool notify(QObject *o, QEvent *e);
        void error(std::exception &e);

    public slots:
        void about();
        void aboutQt();

    private:
        static QString applicationDescription_;
};

#endif /* GEMPP_GUIAPPLICATION_H */
