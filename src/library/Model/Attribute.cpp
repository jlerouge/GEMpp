#include "Attribute.h"

QMetaType::Type Attribute::toType(QString name) {
    if(!name.compare("string", Qt::CaseInsensitive))
        return QMetaType::QString;
    if(!name.compare("char", Qt::CaseInsensitive))
        return QMetaType::QChar;
    return (QMetaType::Type) QMetaType::type(name.toStdString().c_str());
}

QString Attribute::toName(QMetaType::Type type) {
    switch(type) {
        case QMetaType::QString:
            return "string";
        case QMetaType::QChar:
            return "char";
        default:
            break;
    }
    return QMetaType::typeName(type);
}

Attribute::Attribute(QMetaType::Type type, QVariant value) {
    type_ = type;
    value_ = value;
}

Attribute::Attribute(const Attribute &other) {
    type_ = other.getType();
    value_ = other.getValue();
}

Attribute::~Attribute() {}

QMetaType::Type Attribute::getType() const {
    return type_;
}

void Attribute::setType(QMetaType::Type type) {
    type_ = type;
}

bool Attribute::isTextBased() const {
    return (type_ == QMetaType::QString || type_ == QMetaType::QChar);
}

QVariant Attribute::getValue() const {
    return value_;
}

void Attribute::setValue(QVariant value) {
    value_ = value;
}

QString Attribute::toString() const {
    return toString(getType(), getValue());
}

QString Attribute::toString(QMetaType::Type type, QVariant value) {
    switch(type) {
        case QMetaType::Bool:
            return value.toBool()? "true" : "false";
        case QMetaType::UInt:
            return QString::number(value.toUInt());
        case QMetaType::Int:
            return QString::number(value.toInt());
        case QMetaType::Float:
            return QString::number(value.toFloat());
        case QMetaType::Double:
            return QString::number(value.toDouble());
        case QMetaType::QString:
            return value.toString();
        case QMetaType::QChar:
            return value.toChar();
        default:
            Exception("Attribute::toString is not implemented for QMetaType::Type" + QString::number(type));
            break;
    }
    return QString();
}

QVariant Attribute::toVariant(QMetaType::Type type, const QString &string) {
    switch(type) {
        case QMetaType::Bool:
            return (string.compare("true", Qt::CaseInsensitive) == 0);
        case QMetaType::UInt:
            return string.toUInt();
        case QMetaType::Int:
            return string.toInt();
        case QMetaType::Float:
            return string.toFloat();
        case QMetaType::Double:
            return string.toDouble();
        case QMetaType::QString:
            return string;
        case QMetaType::QChar:
            return string.at(0);
        default:
            Exception("Attribute::toVariant is not implemented for QMetaType::Type" + QString::number(type));
            break;
    }
    return QVariant();
}
