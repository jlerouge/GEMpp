#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <QList>
#include "ISaveable.h"
#include "IPrintable.h"
#include "Identified.h"

template <class T>
class DLL_EXPORT PrintableMatrix : virtual public IPrintable {
    public:
        void print(Printer *p) { Q_UNUSED(p); }
    protected:
        QList< QList<T> > matrix_;
};

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

template <class T>
class DLL_EXPORT Matrix : public PrintableMatrix<T>, virtual public ISaveable {
    public:
        Matrix() {}
        Matrix(int rows, int cols, T init) {
            for(int i=0; i<rows; ++i) {
                this->matrix_.append(QList<T>());
                for(int j=0; j<cols; ++j)
                    this->matrix_[i].append(init);
            }
        }
        Matrix(int rows, int cols) {
            T init;
            for(int i=0; i<rows; ++i) {
                this->matrix_.append(QList<T>());
                for(int j=0; j<cols; ++j)
                    this->matrix_[i].append(init);
            }
        }

        ~Matrix() {}

        T getElement(int i, int j) const { return this->matrix_[i][j]; }
        void setElement(int i, int j, T value) { this->matrix_[i][j] = value; }
        void addElement(int i, int j, T value) { this->matrix_[i][j] += value; }
        QList<T> getRow(int i) const { return this->matrix_[i]; }
        QList<T> getCol(int j) const {
            QList<T> res;
            for(auto row : this->matrix_)
                res.push_back(row[j]);
            return res;
        }
        int getRowCount() const { return this->matrix_.size(); }
        int getColCount() const { return this->matrix_[0].size(); }
        int getElementCount() const { return getRowCount() * getColCount(); }
        typename QList<QList<T> >::iterator begin() { return this->matrix_.begin(); }
        typename QList<QList<T> >::iterator end() { return this->matrix_.end(); }
        void symmetrize() {
            for(int i=1; i<getRowCount(); ++i)
                for(int j=0; j<i; ++j)
                    this->matrix_[i][j] = this->matrix_[j][i];
        }

        void save(const QString &filename) { FileStream::saveFile(this, filename); }
};

#endif /*__MATRIX_H__*/
