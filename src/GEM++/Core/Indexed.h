#ifndef GEMPP_INDEXED_H
#define GEMPP_INDEXED_H

#include "../../Portability.h"

/**
 * @brief The Indexed class represents objects
 * that are indexed by a natural integer in another class.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT Indexed {
    public:
        /**
         * @brief Constructs a new empty Indexed object.
         */
        Indexed();

        /**
         * @brief Constructs a copy of another Indexed object.
         */
        Indexed(const Indexed &other);

        /**
         * @brief Constructs a new Indexed object with an index.
         * @param i the index
         */
        Indexed(int index);

        /**
         * @brief Destructs an Indexed object.
         */
        ~Indexed();

        /**
         * @brief Returns the index of the Indexed.
         * @return the value of Indexed::index_
         */
        int getIndex() const;

        /**
         * @brief Sets the index of the Indexed.
         * @param index the new index of the Indexed
         */
        void setIndex(int index);

    protected:
        /**
         * @brief The index of the Indexed.
         */
        int index_;
};

#endif /*INDEXED_H*/
