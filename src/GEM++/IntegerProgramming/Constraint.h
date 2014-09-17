#ifndef __CONSTRAINT_H__
#define __CONSTRAINT_H__

#include "Expression.h"
#include "../Core/Identified.h"

/**
 * @brief The Constraint class represents the mathematical concept of constraints, used in integer Program.
 *
 * Let \f$ \mathbf{x} \f$ be a vector of integer variables, say \f$ \mathbf{x} \in \mathbb{Z}^n \f$.
 *
 * Let \f$ f : \mathbb{Z}^n \rightarrow \mathbb{R} \f$ be a function, and \f$ b \in \mathbb{R} \f$ a constant.
 *
 * There are two types of constraints :
 *   - equality constraints, where \f$ f(\mathbf{x}) = b \f$;
 *   - inequality constraints, where \f$ f(\mathbf{x}) \leq b \f$ or \f$ f(\mathbf{x}) \geq b \f$.
 *
 * \f$ f(\mathbf{x}) \f$ is the Expression, \f$ b \f$ is the right hand side (RHS) and \f$ =, \geq \f$ or
 * \f$ \leq \f$ forms the Constraint::Relation.
 *
 * @see Expression
 * @see Program
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT Constraint : virtual public IPrintable, public Identified {
    public:
        /**
         * @brief The Constraint::Relation enum indicates the type of contraint.
         */
        enum Relation{
            EQUAL, /**< equality constraint (\f$ = \f$) */
            LESS_EQ, /**< inequality constraint (\f$ \leq \f$) */
            GREATER_EQ /**< inequality constraint (\f$ \geq \f$) */
        };

        /**
         * @brief Constructs a new Constraint object, with parameters.
         * @param exp the Expression
         * @param relation the Constraint::Relation
         * @param rhs the right hand side value
         */
        Constraint(Expression *exp, Relation relation, double rhs);

        /**
         * @brief Destructs a Constraint object.
         */
        virtual ~Constraint() = 0;

        /**
         * @brief Returns the Expression.
         * @return the value of Constraint::exp_
         */
        Expression *getExpression();

        /**
         * @brief Returns the Constraint::Relation .
         * @return the value of Constraint::relation_
         */
        Relation getRelation();

        /**
         * @brief Returns the right hand side value.
         * @return the value of Constraint::rhs_
         */
        double getRHS();

        /**
         * @brief Indicates whether the Constraint is satisfied or not,
         * depending on the value of the Expression.
         * @return true if the constraint is satisfied, false otherwise
         */
        virtual bool eval();

        /**
         * @brief Prints the Constraint to a Printer.
         * @param p The Printer
         */
        virtual void print(Printer *p);

        /**
         * @brief Serializes the Constraint into a text string.
         * @return the text string
         */
        virtual QString toString();

    protected:
        /**
         * @brief The Expression of the Constraint.
         */
        Expression *exp_;

        /**
         * @brief The Constraint::Relation of the Constraint.
         */
        Relation relation_;

        /**
         * @brief The right hand side value of the Constraint.
         */
        double rhs_;

    private:
        /**
         * @brief A static counter to maintain unique IDs for all Constraint objects.
         */
        static uint count_;
};

#endif /*__CONSTRAINT_H__*/
