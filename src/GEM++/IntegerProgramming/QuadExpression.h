#ifndef GEMPP_QUADEXPRESSION_H
#define GEMPP_QUADEXPRESSION_H

#include "LinearExpression.h"

/**
 * @brief The QuadExpression class represents the mathematical concept of quadratic expressions, used in QuadConstraint
 *
 * Let \f$ \mathbf{x} = \begin{bmatrix}x_1\\ x_2\\ \vdots\\ x_n \end{bmatrix} \in \mathbb{Z}^n \f$ be a vector of integer variables,
 * and let \f$ f : \mathbb{Z}^n \rightarrow \mathbb{R} \f$ be a quadratic function.
 *
 * Given \f$ \mathbf{a} = \begin{bmatrix}a_0\\ a_1\\ \vdots\\ a_n \end{bmatrix} \in \mathbb{R}^{n+1} \f$, and
 * \f$ B = \begin{bmatrix}b_{1,1}\; \dots\; b_{1,n}\\ \vdots\quad \ddots\quad \vdots\\ b_{n,1}\; \dots\; b_{n,n}\end{bmatrix} \in \mathcal{M}_n(\mathbb{R}) \f$,
 * the function \f$ f \f$ can be written \f$ f(\mathbf{x}) = \mathbf{a}^T \cdot \begin{bmatrix}1\\ \mathbf{x} \end{bmatrix} + \mathbf{x}^T \cdot B \cdot \mathbf{x}
 * = a_0 + \sum_{k=1}^n (a_k \, x_k) + \sum_{i=1}^n \sum_{j=1}^n (b_{i,j} \, x_i \, x_j) \f$.
 *
 * Whereas the linear part (\f$ a_0 + \sum_{k=1}^n (a_k \, x_k) \f$) is already handled by the LinearExpression class,
 * the purely quadratic part (\f$ \sum_{i=1}^n \sum_{j=1}^n (b_{i,j} \, x_i \, x_j) \f$) is implemented via the class QuadExpression, derived from LinearExpression.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT QuadExpression : virtual public LinearExpression {
    public:
        /**
         * @brief Constructs a new empty QuadExpression object.
         */
        QuadExpression();

        /**
         * @brief Destructs a QuadExpression object.
         */
        virtual ~QuadExpression() {} // QuadExpression is polymorphic

        /**
         * @brief Returns the quadratic terms contained in the QuadExpression.
         * @return the value of QuadExpression::quadTerms_
         */
        QHash<Quad, double> &getQuadTerms();

        /**
         * @brief Multiplies the entire QuadExpression (linear and quadratic parts) by a value.
         * @param d the multiplicator
         */
        void multiplyBy(double d);

        /**
         * @brief Adds a quadratic term to the QuadExpression. If the ::Quad concerned by the ::QuadTerm
         * is already present in the QuadExpression, its coefficient is updated.
         */
        void addQuadTerm(QuadTerm t);

        /**
         * @brief Evaluates the QuadExpression on the current state of the variables.
         * @return the current value of the QuadExpression
         */
        double eval();

        /**
         * @brief Indicates whether the QuadExpression is set.
         * @return true if the QuadExpression contains at least one linear or quadratic term, false otherwise.
         */
        bool isSet();

        /**
         * @brief Prints the QuadExpression to a Printer.
         */
        void print(Printer *p);

        /**
         * @brief Serializes the QuadExpression in a QString.
         */
        QString toString();

        /**
         * @brief Sums a QList of Variable in a QuadExpression.
         * @return \f$ \sum_{k=0}^{vars.size()-1} vars[k] \f$
         * @see LinearExpression::sum()
         */
        static QuadExpression *sum(QList<Variable*> &vars);

        /**
         * @brief Sums a QList of ::Quad in a QuadExpression.
         * @return \f$ \sum_{k=0}^{quads.size()-1} quads[k] \f$
         */
        static QuadExpression *sum(QList<Quad> &quads);

    private:
        /**
         * @brief The quadratic terms of the QuadExpression, stored as key-value pairs : the ::Quad
         * is the key whereas the coefficient is the value.
         * Hence, a ::Quad may be present at most one time in the terms, but its coefficient may be updated.
         */
        QHash<Quad, double> quadTerms_;
};

void operator+=(QuadExpression &e, QuadTerm t);
void operator-=(QuadExpression &e, QuadTerm t);

QuadTerm operator*(Variable &v, Term t);
QuadTerm operator*(Term t, Variable &v);
QuadTerm operator*(Quad q, double d);
QuadTerm operator*(double d, Quad q);

QuadExpression *operator+(QuadTerm t1, QuadTerm t2);
QuadExpression *operator-(QuadTerm t1, QuadTerm t2);
QuadExpression *operator+(QuadTerm t1, Term t2);
QuadExpression *operator-(QuadTerm t1, Term t2);
QuadExpression *operator+(Term t1, QuadTerm t2);
QuadExpression *operator-(Term t1, QuadTerm t2);
QuadExpression *operator+(QuadTerm t, double d);
QuadExpression *operator-(QuadTerm t, double d);
QuadExpression *operator+(double d, QuadTerm t);
QuadExpression *operator-(double d, QuadTerm t);
QuadExpression *operator+(QuadExpression *e, QuadTerm t);
QuadExpression *operator-(QuadExpression *e, QuadTerm t);

#endif /*QUADEXPRESSION_H*/
