#ifndef GEMPP_PROGRAM_H
#define GEMPP_PROGRAM_H

#include <QSet>
#include "Variable.h"
#include "../Core/ISaveable.h"

/**
 * @brief The Program class represents the mathematical concept of integer programs, that are used to solve integer
 * optimization problems.
 *
 * Let \f$ x = \begin{bmatrix}x_1\\ x_2\\ \vdots\\ x_n\end{bmatrix} \in \mathbb{Z}^n \f$ be a vector of integer
 * variables and let \f$ f : \mathbb{Z}^n \rightarrow \mathbb{R} \f$ be a function, named the objective function.
 *
 * An integer Program \f$ P \f$ is used to solve an integer optimization problem, that is to say optimizing an
 * objective function over a discrete set, under certain conditions on the integer variables, called the constraints.
 * A Constraint can be either an equality constraint or an inequality constraint.
 *
 * Depending on the context, optimizing an objective function may mean minimizing or maximizing it.
 * Say we want to minimize \f$ f \f$, then \f$ P \f$ can be written :
 *
 * \f$ \underset{\mathbf{x}}{\text{min}} f(\mathbf{x})\\
 * s.c. \left\{ \begin{array}{l} g_i(\mathbf{x}) \leq \mathbf{b} \quad \forall i \in [\![1; p]\!] \\
 *                               h_e(\mathbf{x}) = \mathbf{d} \quad \forall e \in [\![1; q]\!] \\
 *                               x_k \in \mathbb{Z} \quad \forall k \in [\![1; n]\!] \end{array} \right. \f$,
 * where \f$ A \in \mathcal{M}_{p,n}(\mathbb{R}), \mathbf{b} \in \mathbb{R}^{p}, C \in \mathcal{M}_{q,n}(\mathbb{R}), \mathbf{d} \in \mathbb{R}^{q} \f$,
 * and where \f$ p \in \mathbb{N} \f$ is the number of inequality constraints and \f$ q \in \mathbb{N} \f$ is the number of equality constraints.
 *
 * @see Constraint
 * @see Variable
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT Program : virtual public IPrintable, virtual public ISaveable {
    public:
        /**
         * @brief The Sense enum defines the sense of the optimization.
         */
        enum Sense{
            MINIMIZE, /**< minimizing the objective function (\f$ \underset{\mathbf{x}}{\text{min}} f(\mathbf{x}) \f$) */
            MAXIMIZE  /**< maximizing the objective function (\f$ \underset{\mathbf{x}}{\text{max}} f(\mathbf{x}) \f$) */
        };

        /**
         * @brief The Type enum defines the type of the program.
         */
        enum Type{
            LINEAR, /**< linear program */
            QUADRATIC /**< quadratic program */
        };

        /**
         * @brief Constructs a new Program object with a Program::Sense.
         * @param sense The Program::Sense of the Program
         */
        Program(Sense sense);

        /**
         * @brief Destructs a Program object.
         */
        ~Program();

        /**
         * @brief Returns the variables of the Program.
         * @return the value of Program::variables_
         */
        QHash<QString, Variable *> &getVariables();

        /**
         * @brief Gets a Variable by identifier.
         * @return the Variable with the correponding id
         */
        Variable *getVariable(QString id);

        /**
         * @brief Returns the Program::Type of the Program.
         * @return the Program::Type
         */
        virtual Type getType() = 0;

        /**
         * @brief Returns the Program::Sense of the Program.
         * @return the value of Program::sense_
         */
        Sense getSense();

        /**
         * @brief Sets the Program::Sense of the Program.
         * @param sense the Program::Sense to use
         */
        void setSense(Sense sense);

    protected:
        /**
         * @brief Add a Variable to the variables used by the Program.
         * @param v the Variable to add.
         */
        void addVariable(Variable *v);

        /**
         * @brief The Program::Sense of the Program.
         */
        Sense sense_;

        /**
         * @brief The variables that appear in the objective function and the constraints of the Program.
         */
        QHash<QString, Variable *> variables_;
};

#endif /*PROGRAM_H*/
