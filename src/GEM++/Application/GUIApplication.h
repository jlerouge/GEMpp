#ifndef __GUIAPPLICATION_H__
#define __GUIAPPLICATION_H__

#include <QMessageBox>
#include <QApplication>
#include "../../Portability.h"

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

#endif /* __GUIAPPLICATION_H__ */
