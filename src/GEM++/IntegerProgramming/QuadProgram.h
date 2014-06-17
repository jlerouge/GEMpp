#ifndef __QUADPROGRAM_H__
#define __QUADPROGRAM_H__

#include "Program.h"
#include "LinearConstraint.h"
#include "QuadConstraint.h"
#include "../Core/Constants.h"
#include "../Core/FileStream.h"

/**
 * @brief The QuadProgram class represents the mathematical concept of quadratic integer program.
 *
 * In comparison to a Program, the objective function of a QuadProgram must be quadratic,
 * and its constraints can be either linear or quadratic.
 *
 * @see LinearConstraint
 * @see QuadConstraint
 * @see QuadExpression
 * @see Program
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT QuadProgram : public Program {
    public:
        /**
         * @brief Constructs a new QuadProgram object with a Program::Sense.
         * @param sense The Program::Sense of the QuadProgram
         */
        QuadProgram(Sense sense);

        /**
         * @brief Destructs a LinearProgram object.
         */
        ~QuadProgram();

        /**
         * @brief Returns the Program::Type of the QuadProgram.
         * @return Program::QUADRATIC
         */
        Type getType();

        /**
         * @brief Returns the quadratic constraints of the QuadProgram.
         * @return the value of QuadProgram::quadConstraints_
         */
        QMap<QString, QuadConstraint *> &getQuadConstraints();

        /**
         * @brief Returns the linear constraints of the QuadProgram.
         * @return the value of QuadProgram::linearConstraints_
         */
        QMap<QString, LinearConstraint *> &getLinearConstraints();

        /**
         * @brief Add a new QuadConstraint to the QuadProgram.
         * @param c the QuadConstraint to add
         */
        void addQuadConstraint(QuadConstraint *c);

        /**
         * @brief Add a new LinearConstraint to the QuadProgram.
         * @param c the LinearConstraint to add
         */
        void addLinearConstraint(LinearConstraint *c);

        /**
         * @brief Returns the objective function of the QuadProgram, as a QuadExpression.
         * @return the value of QuadProgram::objective_
         */
        QuadExpression *getObjective();

        /**
         * @brief Sets the objective function of the QuadProgram.
         * @param e the QuadExpression representing the objective function to set
         */
        void setObjective(QuadExpression *e);

        /**
         * @brief Prints the QuadProgram to a Printer.
         * @param p the Printer
         */
        void print(Printer *p);

        /**
         * @brief Saves the QuadProgram to a file.
         * @param filename the path to the file
         */
        void save(const QString &filename);

    private:
        /**
         * @brief The objective function of the QuadProgram, expressed as a QuadExpression.
         */
        QuadExpression *objective_;

        /**
         * @brief the quadratic constraints of the QuadProgram.
         */
        QMap<QString, QuadConstraint *> quadConstraints_;

        /**
         * @brief the linear constraints of the QuadProgram.
         */
        QMap<QString, LinearConstraint *> linearConstraints_;
};

void operator+=(QuadProgram &lp, LinearConstraint *c);
void operator+=(QuadProgram &lp, QuadConstraint *c);
void operator+=(QuadProgram &lp, QuadExpression *e);

#endif /*__QUADPROGRAM_H__*/
