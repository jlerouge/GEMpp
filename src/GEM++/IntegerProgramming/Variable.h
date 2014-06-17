#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <QHash>
#include <QPair>
#include <stdexcept>
#include "../Core/Identified.h"
#include "../Core/IPrintable.h"

class Variable;

/**
 * @brief The ::Term type represents the multiplication of a variable by a coefficient as a pair. It is the constituting element of a LinearExpression.
 * @see LinearExpression
 */
typedef QPair<Variable*, double> Term;

/**
 * @brief The ::Quad type represents the multiplication of two variables as a pair.
 */
typedef QPair<Variable*, Variable *> Quad;

/**
 * @brief The ::QuadTerm type represents the multiplication a ::Quad by a coefficient as a pair. It is the constituting element of a QuadExpression.
 * @see QuadExpression
 */
typedef QPair<Quad, double> QuadTerm;


/**
 * @brief The Variable class represents the mathematical concept of integer variable, used in integer Program.
 *
 * An integer Variable \f$ x \f$ can be a general integer (\f$ x \in \mathbb{Z} \f$), a natural integer (\f$ x \in \mathbb{N} \f$),
 * a bounded integer, i.e. an integer that belongs to an integer interval (\f$ x \in [\![a, b]\!] \f$ where \f$ (a,b) \in \mathbb{Z}^2, a \leq b \f$)
 * or a binary (\f$ x \in \mathbb{B} = \{0; 1\} \f$).
 *
 */
class DLL_EXPORT Variable : virtual public IPrintable, public Identified {
    public:
        /**
         * @brief The Type enum describes the type of the integer Variable.
         */
        enum Type{
            BOUNDED, /**< a bounded integer variable (\f$ x \in [\![a, b]\!] \f$ where \f$ (a,b) \in \mathbb{Z}^2, a \leq b \f$) */
            BINARY, /**< a binary variable (\f$ x \in \mathbb{B} = \{0; 1\} \f$) */
            CONTINUOUS /**< a continuous variable \f$) */
        };

        /**
         * @brief Constructs a new Variable object, with parameters.
         * For a binary Variable, given bounds are ignored and set to \f$ {0;1} \f$.
         * @param id The identifier of the Variable
         * @param type The Variable::Type of the Variable
         * @param lowerBound The integer lower bound of the Variable (0 for a binary)
         * @param upperBound The integer upper bound of the Variable (1 for a binary)
         */
        Variable(QString id, Type type=BINARY, int lowerBound=0, int upperBound=1);

        /**
         * @brief Destructs a Variable object.
         */
        ~Variable();

        /**
         * @brief Returns the Variable::Type of the Variable.
         * @return the value of Variable::type_
         */
        Type getType();

        /**
         * @brief Sets the Variable::Type of the Variable.
         * @param type Variable::Type to set
         */
        void setType(Type type);

        /**
         * @brief Returns the integer lower bound of the Variable.
         * @return the value of Variable::lowerBound_
         */
        int getLowerBound();

        /**
         * @brief Sets the integer lower bound of the Variable.
         * @param low the lower bound to set
         */
        void setLowerBound(int low);

        /**
         * @brief Returns the integer upper bound of the Variable.
         * @return the value of Variable::upperBound_
         */
        int getUpperBound();

        /**
         * @brief Sets the integer upper bound of the Variable.
         * @param up the upper bound to set
         */
        void setUpperBound(int up);

        /**
         * @brief (Re-)activates a variable, i.e. resets its bounds to \f$ [\![\textrm{low};\textrm{up}]\!] \f$.
         * For a binary Variable, given bounds are ignored and set to \f$ {0;1} \f$.
         */
        void activate(int low = 0, int up = 1);

        /**
         * @brief Deactivates a variable, i.e. sets its both bounds to 0.
         */
        void deactivate();

        /**
         * @brief Tests if a Variable is active, i.e. its bounds are not both 0.
         * @return whether the Variable is active
         */
        bool isActive();

        /**
         * @brief Tests if a Variable is active, i.e. its bounds are not both 0.
         * @return whether the Variable is active
         */
        void addColumn(QString id, double d);
        QHash<QString, double> &getColumns();
        double getColumn(QString id);
        void setValue(int val);
        int eval();

        void print(Printer *p);
        operator Term() const;

    private:
        QHash<QString, double> columns_;
        int upperBound_;
        int lowerBound_;
        int value_;
        Type type_;
};

/**
 * @brief Tests the equality of two quads. A ::Quad equals another ::Quad if they have the same variables, independently from their order in the pair.
 * @param q1 the first ::Quad
 * @param q2 the second ::Quad
 * @return true if the quads are equal, false otherwise
 */
bool operator==(Quad q1, Quad q2);

/**
 * @brief Tests the equality of two quads. A ::Quad equals another ::Quad if they have the same variables, independently from their order in the pair.
 * @param q1 the first ::Quad
 * @param q2 the second ::Quad
 * @return true if the quads are equal, false otherwise
 */
bool isActive(QuadTerm t);

#endif /*__VARIABLE_H__*/
