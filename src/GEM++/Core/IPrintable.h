#ifndef GEMPP_IPRINTABLE_H
#define GEMPP_IPRINTABLE_H

#include "Printer.h"

/**
 * @brief The IPrintable class is an interface for printable objects.
 *
 * These particular objects can be converted to plain text and printed
 * to standard output with a Printer.
 *
 * @warning This interface must be implemented to be used.
 * @see ISaveable
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT IPrintable {
    public:
        /**
         * @brief Destructs an IPrintable.
         */
        virtual ~IPrintable() {}

        /**
         * @brief Prints an IPrintable to a Printer.
         * @param p the Printer
         */
        virtual void print(Printer *p) = 0;

        /**
         * @brief Shows an IPrintable using a Printer.
         */
        virtual void show() {
            Printer p;
            print(&p);
            p.show();
        }
};

#endif /*IPRINTABLE_H*/
