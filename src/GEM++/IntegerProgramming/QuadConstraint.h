#ifndef __QUADCONSTRAINT_H__
#define __QUADCONSTRAINT_H__

#include "Constraint.h"
#include "QuadExpression.h"

/**
 * @brief The QuadConstraint class represents the mathematical concept of quadratic constraints, used in QuadProgram
 *
 * In comparison to a Constraint, a QuadConstraint must have a QuadExpression as its expression.
 *
 * @see Constraint
 * @see QuadExpression
 * @see QuadProgram
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT QuadConstraint : virtual public Constraint {
    public:

        /**
         * @brief Constructs a new QuadConstraint, with parameters.
         * @param exp the QuadExpression
         * @param relation the Constraint::Relation
         * @param rhs the right hand side value
         */
        QuadConstraint(QuadExpression *exp, Relation relation, double rhs, QString uid);

        /**
         * @brief Destructs a QuadConstraint.
         */
        ~QuadConstraint();

        /**
         * @brief Returns the QuadExpression of the QuadConstraint.
         * @return the value of Constraint::exp_, casted as QuadExpression
         */
        QuadExpression *getQuadExpression();

        /**
         * @brief Indicates whether the QuadConstraint is satisfied or not,
         * depending on the value of the QuadExpression.
         * @return true if the quadratic constraint is satisfied, false otherwise
         */
        bool eval();

        /**
         * @brief Prints the QuadConstraint to a Printer.
         * @param p The Printer
         */
        void print(Printer *p);

        /**
         * @brief Serializes the QuadConstraint in a QString.
         * @return the text string
         */
        QString toString();
};

#endif /*__QUADCONSTRAINT_H__*/
