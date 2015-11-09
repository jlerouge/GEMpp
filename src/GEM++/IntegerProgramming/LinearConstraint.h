#ifndef GEMPP_LINEARCONSTRAINT_H
#define GEMPP_LINEARCONSTRAINT_H

#include "Constraint.h"
#include "LinearExpression.h"

/**
 * @brief The LinearConstraint class represents the mathematical concept of linear constraints, used in LinearProgram.
 *
 * In comparison to a Constraint, a LinearConstraint must have a LinearExpression as its expression.
 *
 * @see Constraint
 * @see LinearExpression
 * @see LinearProgram
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT LinearConstraint : virtual public Constraint {
    public:

        /**
         * @brief Constructs a new LinearConstraint, with parameters.
         * @param exp the LinearExpression
         * @param relation the Constraint::Relation
         * @param rhs the right hand side value
         */
        LinearConstraint(LinearExpression *exp, Relation relation, double rhs);

        /**
         * @brief Destructs a LinearConstraint.
         */
        ~LinearConstraint();

        /**
         * @brief Returns the LinearExpression of the LinearConstraint.
         * @return the value of Constraint::exp_, casted as LinearExpression
         */
        LinearExpression *getLinearExpression();

        /**
         * @brief Indicates whether the LinearConstraint is satisfied or not,
         * depending on the value of the LinearExpression.
         * @return true if the linear constraint is satisfied, false otherwise
         */
        bool eval();

        /**
         * @brief Prints the LinearConstraint to a Printer.
         * @param p The Printer
         */
        void print(Printer *p);

        /**
         * @brief Serializes the LinearConstraint into a text string.
         * @return the text string
         */
        QString toString();
};

#endif /*LINEARCONSTRAINT_H*/
