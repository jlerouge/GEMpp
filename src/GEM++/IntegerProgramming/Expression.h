#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include "../Core/IPrintable.h"

/**
 * @brief The Expression class represents the mathematical expression of a Constraint.
 *
 * Let \f$ \mathbf{x} \f$ be a vector of integer variables, say \f$ \mathbf{x} \in \mathbb{Z}^n \f$,
 * and let \f$ f : \mathbb{Z}^n \rightarrow \mathbb{R} \f$ be a function. Then, \f$ f(\mathbf{x}) \f$
 * is named an Expression.
 *
 * Its value depends on the values taken by the variables \f$ \mathbf{x} \f$. If there is a constant part
 * in \f$ f(\mathbf{x}) \f$ that doesn't depend on \f$ \mathbf{x} \f$, this expression can be rewritten
 * \f$ f(\mathbf{x}) = g(\mathbf{x}) + c\f$, where \f$ c \in \mathbb{R} \f$.
 *
 * The Expression class handles only the constant \f$ c \f$, while \f$ g(\mathbf{x}) \f$ has to be defined with a derived class.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT Expression : virtual public IPrintable {
    public:
        /**
         * @brief Constructs a new empty Expression object.
         */
        Expression();

        /**
         * @brief Destructs an Expression object.
         */
        virtual ~Expression() {}

        /**
         * @brief Returns the constant part of the Expression.
         * @return the value of Expression::const_
         */
        double getConst();

        /**
         * @brief Adds a value to the constant part of the Expression.
         * @param d the value to add
         */
        void addConst(double d);

        /**
         * @brief Multiplies the constant part of the Expression by a value.
         * @param d the multiplicator
         */
        void multiplyBy(double d);

        /**
         * @brief Returns the constant part of the Expression.
         * @return the value of Expression::const_
         * @see getConst()
         */
        double eval();

        /**
         * @brief Prints the Expression to a Printer.
         * @param p The Printer
         */
        void print(Printer *p);

        /**
         * @brief Serializes the Expression into a text string.
         * @return the text string
         */
        QString toString();


    protected:
        /**
         * @brief The constant part of the Expression.
         */
        double const_;
};

/**
 * @brief Adds a constant term to an Expression.
 * @param e The Expression
 * @param d The constant
 */
void operator+=(Expression &e, double d);

/**
 * @brief Substracts a constant term from an Expression.
 * @param e The Expression
 * @param d The constant
 */
void operator-=(Expression &e, double d);

#endif /*__EXPRESSION_H__*/
