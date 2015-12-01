#ifndef GEMPP_GUIAPPLICATION_H
#define GEMPP_GUIAPPLICATION_H

#include <QMessageBox>
#include <QApplication>
#include "Core/Portability.h"
#include "Core/Constants.h"

/**
 * @brief The GUIApplication class implements graphical user interface applications.
 * @author Julien Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT GUIApplication : public QApplication {
        Q_OBJECT
    public:
        /**
         * @brief Constructs a new GUIApplication object with parameters.
         * @param argc the number of command line arguments
         * @param argv the array of command line arguments
         */
        GUIApplication(int &argc, char **argv);

        /**
         * @brief Destructs a ConsoleApplication object
         */
        ~GUIApplication();

        /**
         * @brief Sets the description of the application.
         * @param description the description
         */
        static void setApplicationDescription(const QString &description);

        /**
         * @brief Returns the description of the application.
         * @return the description
         */
        static QString applicationDescription();

        /**
         * @brief Returns the created instance of the GUIApplication.
         * @return the GUIApplication
         */
        static GUIApplication *instance();

        /**
         * @brief Hooks the exceptions up and tries to propagate it,
         * or show an error message and exits if the exception is not caught.
         */
        virtual bool notify(QObject *o, QEvent *e);


        /**
         * @brief Displays an error message and exits.
         */
        void error(std::exception &e);

    public slots:
        /**
         * @brief Displays an info box about the software.
         */
        void about();

        /**
         * @brief Displays an info box about Qt.
         */
        void aboutQt();

    private:
        /**
         * @brief The description of the application.
         */
        static QString applicationDescription_;
};

#endif /* GEMPP_GUIAPPLICATION_H */
