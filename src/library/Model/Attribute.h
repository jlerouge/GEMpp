#ifndef GEMPP_ATTRIBUTE_H
#define GEMPP_ATTRIBUTE_H

#include <QMetaType>
#include <QVariant>
#include "Core/Constants.h"

/**
 * @brief The Attribute class represents the attribute of a ::Attribute. An attribute
 * may be of various type, e.g boolean, numeric, string based, or taken from a discrete set.
 * These are the atomic elements used to compute the substitution and creation costs.
 *
 * As for now, the useable QMetaType::Type values are the following :
 *     - Bool
 *     - Int
 *     - Float
 *     - Double
 *     - QString
 *     - QChar
 *
 * @see Attribute
 * @see Weight
 */
class DLL_EXPORT Attribute {
    public:
        /**
         * @brief Returns the name of the type.
         * @param type the type
         * @return the name
         */
        static QString toName(QMetaType::Type type);

        /**
         * @brief Retrieves the type from its name.
         * @param name the name
         * @return the type
         */
        static QMetaType::Type toType(QString name);

        /**
         * @brief Constructs a new Attribute object.
         */
        Attribute(QMetaType::Type type, QVariant value);

        /**
         * @brief Constructs a copy of an existing Attribute object.
         * @param other the Attribute to copy
         */
        Attribute(const Attribute &other);

        /**
         * @brief Destructs a Attribute object.
         */
        virtual ~Attribute();

        /**
         * @brief Returns the type of the attribute.
         * @return the type
         */
        QMetaType::Type getType() const;

        /**
         * @brief Sets the type of the attribute.
         * @param the type
         */
        void setType(QMetaType::Type type);

        /**
         * @brief Indicates whether this attribute is text based (QString or QChar type).
         * @return a boolean
         */
        bool isTextBased() const;

        /**
         * @brief Returns the value of the attribute.
         * @return the value
         */
        QVariant getValue() const;

        /**
         * @brief Sets the type of the attribute.
         * @param the type
         */
        void setValue(QVariant value);

        /**
         * @brief Serializes an attribute as string, depending on its type.
         * @param attribute the attribute
         * @return its string representation
         * @warning throws an exception if the conversion for the attribute type is not implemented
         */
        QString toString() const;

        /**
         * @brief Serializes a variable object as string, depending on its type.
         * @param type the type of the object
         * @param value its value
         * @return its string representation
         * @warning throws an exception if the conversion for a type is not implemented
         */
        static QString toString(QMetaType::Type type, QVariant value);

        /**
         * @brief Deserializes a variable object from string, depending on its type.
         * @param type the type of the object
         * @param string its string representation
         * @return its value
         * @warning throws an exception if the conversion for a type is not implemented
         */
        static QVariant toVariant(QMetaType::Type type, const QString &string);

    private:
        /**
         * @brief The creation cost of the element.
         */
        QMetaType::Type type_;

        /**
         * @brief The attributes of the element.
         */
        QVariant value_;
};

#endif /* GEMPP_GRAPHELEMENT_H */
