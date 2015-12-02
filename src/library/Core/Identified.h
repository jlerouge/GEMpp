#ifndef GEMPP_IDENTIFIED_H
#define GEMPP_IDENTIFIED_H

#include "Constants.h"

/**
 * @brief The Identified class represents objects that have a text identifier.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT Identified
{
    public:
        /**
         * @brief Constructs a new empty Identified object.
         */
        Identified();

        /**
         * @brief Constructs a copy of another Identified object.
         */
        Identified(const Identified &other);

        /**
         * @brief Constructs a new Identified object with an identifier.
         * @param id the identifier
         */
        Identified(QString id);

        /**
         * @brief Destructs an Identified object.
         */
        ~Identified();

        /**
         * @brief Returns the identifier of the Identified.
         * @return the value of Identified::id_
         */
        const QString &getID() const;

        /**
         * @brief Sets the identifier of the Identified.
         * @param id the new identifier of the Identified
         */
        void setID(QString id);

    protected:
        /**
         * @brief The identifier of the Identified.
         */
        QString id_;
};

#endif /* GEMPP_IDENTIFIED_H */
