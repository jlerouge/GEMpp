#ifndef __LINEARPROGRAM_H__
#define __LINEARPROGRAM_H__

#include "Program.h"
#include "LinearConstraint.h"
#include "../Core/Constants.h"
#include "../Core/FileStream.h"

/**
 * @brief The LinearProgram class represents the mathematical concept of linear integer program.
 *
 * In comparison to a Program, the objective function and the constraints of a LinearProgram must be linear.
 *
 * @see LinearConstraint
 * @see LinearExpression
 * @see Program
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT LinearProgram : public Program {
    public:
        /**
         * @brief The Output enum specifies the output format to be used to save the LinearProgram.
         */
        enum Output{
            LP, /**< the .lp linear program format */
            MPS /**< the .mps linear program format */
        };

        /**
         * @brief Constructs a new LinearProgram object with a Program::Sense.
         * @param sense The Program::Sense of the QuadProgram
         */
        LinearProgram(Sense sense);

        /**
         * @brief Destructs a LinearProgram object.
         */
        ~LinearProgram();

        /**
         * @brief Returns the Program::Type of the LinearProgram.
         * @return Program::LINEAR
         */
        Type getType();

        /**
         * @brief Returns the linear constraints of the LinearProgram.
         * @return the value of LinearProgram::constraints_
         */
        QMap<QString, LinearConstraint *> &getConstraints();

        /**
         * @brief Add a new LinearConstraint to the LinearProgram.
         * @param c the LinearConstraint to add
         */
        void addLinearConstraint(LinearConstraint *c);

        //void clearConstraints();

        /**
         * @brief Returns the objective function of the LinearProgram, as a LinearExpression.
         * @return the value of LinearProgram::objective_
         */
        LinearExpression *getObjective();

        /**
         * @brief Sets the objective function of the LinearProgram.
         * @param e the LinearExpression representing the objective function to set
         */
        void setObjective(LinearExpression *e);

        /**
         * @brief Returns the output format of the LinearProgram.
         * @return the value of LinearProgram::out_
         */
        Output getOutput();

        /**
         * @brief Sets the output format of the LinearProgram.
         * @param out the LinearProgram::Output to set
         */
        void setOutput(Output out);

        /**
         * @brief Prints the LinearProgram to a Printer, according to the LinearProgram::Output format.
         * @param p the Printer
         */
        void print(Printer *p);

        /**
         * @brief Saves the LinearProgram to a file. The LinearProgram::Output format (LinearProgram::LP or LinearProgram::MPS) is chosen according to the filename extension (.lp or .mps).
         * @param filename the path to the file
         */
        void save(const QString &filename);

    private:
        /**
         * @brief The LinearProgram::Output format to use for the print() method.
         */
        Output out_;

        /**
         * @brief The objective function of the LinearProgram, expressed as a LinearExpression.
         */
        LinearExpression *objective_;

        /**
         * @brief the linear constraints of the LinearProgram.
         */
        QMap<QString, LinearConstraint *> constraints_;

        /**
         * @brief Prints the LinearProgram to a Printer, in the MPS format.
         * @param p The Printer
         */
        void printMPS(Printer *p);
        /**
         * @brief Prints the LinearProgram to a Printer, in the LP format.
         * @param p The Printer
         */
        void printLP(Printer *p);
};

void operator+=(LinearProgram &lp, LinearConstraint *c);
void operator+=(LinearProgram &lp, LinearExpression *e);

#endif /*__LINEARPROGRAM_H__*/
