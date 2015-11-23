#ifndef GEMPP_LINEAREXPRESSION_H
#define GEMPP_LINEAREXPRESSION_H

#include <QList>
#include "Variable.h"
#include "Expression.h"

/**
 * @brief The LinearExpression class represents the mathematical concept of linear expressions, used in LinearConstraint.
 *
 * Let \f$ \mathbf{x} = \begin{bmatrix}x_1\\ x_2\\ \vdots\\ x_n \end{bmatrix} \in \mathbb{Z}^n \f$ be a vector of integer variables,
 * and let \f$ f : \mathbb{Z}^n \rightarrow \mathbb{R} \f$ be a linear function.
 *
 * Given \f$ \mathbf{a} = \begin{bmatrix}a_0\\ a_1\\ \vdots\\ a_n \end{bmatrix} \in \mathbb{R}^{n+1} \f$, the function \f$ f \f$ can
 * be written \f$ f(\mathbf{x}) = \mathbf{a}^T \cdot \begin{bmatrix}1\\ \mathbf{x} \end{bmatrix} = \begin{bmatrix} a_0\; a_1\; \dots\; a_n \end{bmatrix}
 * \cdot \begin{bmatrix}1\\ x_1\\ \vdots\\ x_n \end{bmatrix} = a_0 + \sum_{k=1}^n (a_k \, x_k) \f$.
 *
 * Whereas the constant (\f$ a_0 \in \mathbb{R} \f$) is already handled by the Expression class,
 * the linear part (\f$ \sum_{k=1}^n (a_k \, x_k) \f$) is implemented via the LinearExpression class, derived from Expression.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT LinearExpression : virtual public Expression {
    public:
        /**
         * @brief Constructs a new empty LinearExpression object.
         */
        LinearExpression();

        /**
         * @brief Destructs a LinearExpression object.
         */
        virtual ~LinearExpression() {} // LinearExpression is polymorphic

        /**
         * @brief Returns the linear terms contained in the LinearExpression.
         * @return the value of LinearExpression::terms_
         */
        QHash<Variable*, double> &getTerms();

        /**
         * @brief Multiplies the entire LinearExpression (constant and linear parts) by a value.
         * @param d the multiplicator
         */
        void multiplyBy(double d);

        /**
         * @brief Adds a linear Term to the LinearExpression. If the Variable concerned by the Term
         * is already present in the LinearExpression, its coefficient is updated.
         * @param t The Term to add
         */
        void addTerm(Term t);

        /**
         * @brief Evaluates the LinearExpression on the current state of the variables.
         * @return the current value of the LinearExpression
         */
        double eval();

        /**
         * @brief Indicates whether the LinearExpression is set.
         * @return true if the LinearExpression contains at least one term, false otherwise.
         */
        bool isSet();

        /**
         * @brief Prints the LinearExpression to a Printer.
         * @param p The Printer
         */
        void print(Printer *p);

        /**
         * @brief Serializes the LinearExpression into a text string.
         * @return the text string
         */
        QString toString();


        /**
         * @brief Sums a QList of Variable in a LinearExpression.
         * @return \f$ \sum_{k=0}^{vars.size()-1} vars[k] \f$
         */
        static LinearExpression *sum(QList<Variable*> vars);

    private:
        /**
         * @brief The linear terms of the LinearExpression, stored as key-value pairs : the Variable
         * is the key whereas the coefficient is the value. Thus, a Variable may be present at most
         * one time in the terms, but its coefficient may be updated.
         */
        QHash<Variable*, double> terms_;
};

/**
 * @brief Adds a linear term to a LinearExpression.
 * @param e The Expression
 * @param d The linear term
 * @see LinearExpression::addTerm()
 */
void operator+=(LinearExpression &e, Term t);
void operator-=(LinearExpression &e, Term t);

Term operator*(Variable &v, double d);
Term operator*(double d, Variable &v);
LinearExpression *operator+(Term t1, Term t2);
LinearExpression *operator-(Term t1, Term t2);
LinearExpression *operator+(Term t, double d);
LinearExpression *operator-(Term t, double d);
LinearExpression *operator+(double d, Term t);
LinearExpression *operator-(double d, Term t);
LinearExpression *operator+(LinearExpression *e, Term t);
LinearExpression *operator-(LinearExpression *e, Term t);


#endif /*LINEAREXPRESSION_H*/
