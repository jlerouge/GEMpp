#ifndef GEMPP_QScienceSpinBox_H
#define GEMPP_QScienceSpinBox_H

#include <QDoubleSpinBox>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QVariant>
#include <QDebug>
#include <QString>

bool isIntermediateValueHelper(qint64 num, qint64 minimum, qint64 maximum, qint64 *match = 0);

class QScienceSpinBox : public QDoubleSpinBox
{
Q_OBJECT
public:
    QScienceSpinBox(QWidget * parent = 0);

    int decimals() const;
    void setDecimals(int value);

    QString textFromValue ( double value ) const;
    double valueFromText ( const QString & text ) const;

private:
    int dispDecimals;
    QChar delimiter, thousand;
    QDoubleValidator * v;


private:
    void initLocalValues(QWidget *parent);
    bool isIntermediateValue(const QString &str) const;
    QVariant validateAndInterpret(QString &input, int &pos, QValidator::State &state) const;
    QValidator::State validate(QString &text, int &pos) const;
    void fixup(QString &input) const;
    QString stripped(const QString &t, int *pos) const;
    double round(double value) const;
    void stepBy(int steps);

public slots:
    void stepDown();
    void stepUp();

};

#endif
