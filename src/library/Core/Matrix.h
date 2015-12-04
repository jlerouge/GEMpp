#ifndef GEMPP_MATRIX_H
#define GEMPP_MATRIX_H

#include <QList>
#include "ISaveable.h"
#include "IPrintable.h"
#include "Identified.h"
#include "FileUtils.h"

/**
 * @brief The PrintableMatrix class is a template class that represents a matrix whose elements can be displayed.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
template <class T>
class DLL_EXPORT PrintableMatrix : virtual public IPrintable {
    public:
        void print(Printer *p) { Q_UNUSED(p); }
    protected:
        QList< QList<T> > matrix_;
};

/**
 * @brief The PrintableMatrix<double> class implements the PrintableMatrix template for double elements.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
template <>
class DLL_EXPORT PrintableMatrix<double> : virtual public IPrintable {
    public:
        void print(Printer *p) {
            QString s;
            for(auto row : matrix_) {
                s = "";
                for(auto col : row)
                    s.append(QString::number(col)+" ");
                p->dump(s);
            }
        }
    protected:
        QList< QList<double> > matrix_;
};

/**
 * @brief The PrintableMatrix<double> class implements the PrintableMatrix template for Identified elements.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
template <>
class DLL_EXPORT PrintableMatrix<Identified *> : virtual public IPrintable {
    public:
        void print(Printer *p) {
            QString s;
            for(auto row : matrix_) {
                s = "";
                for(auto col : row)
                    s.append(col->getID()+" ");
                p->dump(s);
            }
        }
    protected:
        QList< QList<Identified *> > matrix_;
};

/**
 * @brief The Matrix class is a template class that represents a general matrix.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
template <class T>
class DLL_EXPORT Matrix : public PrintableMatrix<T>, virtual public ISaveable {
    public:
        /**
         * @brief Constructs a new Matrix object.
         */
        Matrix() {}

        /**
         * @brief Constructs a new Matrix object, with fixed size and an initial element.
         * @param rows the row number of the matrix
         * @param cols the column number of the matrix
         * @param init the element used to initialize the matrix
         */
        Matrix(int rows, int cols, T init) {
            for(int i=0; i<rows; ++i) {
                this->matrix_.append(QList<T>());
                for(int j=0; j<cols; ++j)
                    this->matrix_[i].append(init);
            }
        }

        /**
         * @brief Constructs a new Matrix object, with fixed size.
         * The initial element is undefined.
         * @param rows the row number of the matrix
         * @param cols the column number of the matrix
         */
        Matrix(int rows, int cols) {
            T init;
            for(int i=0; i<rows; ++i) {
                this->matrix_.append(QList<T>());
                for(int j=0; j<cols; ++j)
                    this->matrix_[i].append(init);
            }
        }

        /**
         * @brief Destructs a Matrix object.
         */
        ~Matrix() {}

        /**
         * @brief Returns the element of the Matrix at position [i, j].
         * @param i the row index
         * @param j the column index
         * @return the element at [i, j]
         */
        T getElement(int i, int j) const { return this->matrix_[i][j]; }

        /**
         * @brief Sets the value of the element of the Matrix at position [i, j].
         * @param i the row index
         * @param j the column index
         * @param value the new value
         */
        void setElement(int i, int j, T value) { this->matrix_[i][j] = value; }

        /**
         * @brief Adds a value to the element of the Matrix at position [i, j].
         * @param i the row index
         * @param j the column index
         * @param value the value to add
         */
        void addElement(int i, int j, T value) { this->matrix_[i][j] += value; }

        /**
         * @brief Returns one row of the Matrix.
         * @param i the row index
         * @return the i-th row
         */
        QList<T> getRow(int i) const { return this->matrix_[i]; }

        /**
         * @brief Returns one column of the Matrix.
         * @param j the column index
         * @return the j-th column
         */
        QList<T> getCol(int j) const {
            QList<T> res;
            for(auto row : this->matrix_)
                res.push_back(row[j]);
            return res;
        }

        /**
         * @brief Returns the row number of the Matrix.
         * @return the row number
         */
        int getRowCount() const { return this->matrix_.size(); }

        /**
         * @brief Returns the column number of the Matrix.
         * @return the column number
         */
        int getColCount() const { return this->matrix_[0].size(); }

        /**
         * @brief Returns the number of elements of the Matrix.
         * @return the number of elements
         */
        int getElementCount() const { return getRowCount() * getColCount(); }

        /**
         * @brief Returns an iterator on the Matrix, poiting to the first element.
         * @return an iterator
         */
        typename QList<QList<T> >::iterator begin() { return this->matrix_.begin(); }

        /**
         * @brief Returns an iterator on the Matrix, poiting after the last element.
         * @return an iterator
         */
        typename QList<QList<T> >::iterator end() { return this->matrix_.end(); }

        /**
         * @brief Makes the Matrix symmetrical by copying the values from the upper-right triangle to the lower-left triangle.
         */
        void symmetrize() {
            for(int i=1; i<getRowCount(); ++i)
                for(int j=0; j<i; ++j)
                    this->matrix_[i][j] = this->matrix_[j][i];
        }

        /**
         * @brief Saves the Matrix in a file by printing its values.
         * @param filename the path to the file
         */
        void save(const QString &filename) { FileUtils::save(this, filename); }
};

#endif /* GEMPP_MATRIX_H */
