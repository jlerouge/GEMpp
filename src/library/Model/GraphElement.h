#ifndef GEMPP_GRAPHELEMENT_H
#define GEMPP_GRAPHELEMENT_H

#include <QMap>
#include "Core/IPrintable.h"
#include "Core/Identified.h"
#include "Core/Indexed.h"

/**
 * @brief The GraphElement class represents an abstract element of a ::Graph, i.e. a ::Vertex or an ::Edge.
 * These elements have attributes, and it is possible to compute substitution costs between two ::GraphElement
 * of the same type as well as the creation cost of a single ::GraphElement, using the substitution and creation
 * ::Weights.
 * @see Edge
 * @see Vertex
 * @see Graph
 * @see Weights
 */
class DLL_EXPORT GraphElement : virtual public IPrintable, virtual public Identified, virtual public Indexed {
        friend class Vertex;
        friend class Edge;
    public:
        /**
         * @brief Indicates the type of the GraphElement.
         */
        enum Type{
            VERTEX = 0, /**< a ::Vertex */
            EDGE, /**< an ::Edge */
            COUNT /**< used to iterate on GraphElement::Type enum */
        };

        /**
         * @brief The names of the types.
         */
        static const char *typeName[COUNT];

        /**
         * @brief Returns the name of the type.
         * @param type the type
         * @return the name
         */
        static QString toName(Type type);

        /**
         * @brief Retrieves the type from its name.
         * @param name the name
         * @return the type
         */
        static Type fromName(QString name);

        /**
         * @brief Constructs a new GraphElement object.
         */
        GraphElement();

        /**
         * @brief Constructs a copy of an existing GraphElement object.
         * @param other the GraphElement to copy
         */
        GraphElement(const GraphElement &other);

        /**
         * @brief Destructs a GraphElement object.
         */
        virtual ~GraphElement();


        /**
         * @brief Returns the creation cost of this element.
         * @return the creation cost
         */
        double getCost() const;

        /**
         * @brief Sets the creation cost of this element.
         * @param d the creation cost
         */
        void setCost(double d);

        /**
         * @brief Returns the type of this element.
         * @return the type
         */
        Type getType() const;

        /**
         * @brief Adds a numeric attribute to the element.
         * @param attribute the attribute name
         * @param value the numeric value
         */
        void addNumericAttribute(const QString &attribute, double value);

        /**
         * @brief Returns a numeric attribute value.
         * @param attribute the attribute name
         * @return the numeric value
         */
        double getNumericAttribute(QString attribute) const;

        /**
         * @brief Returns all numeric attributes.
         * @return the numeric attributes
         */
        const QMap<QString, double> &getNumericAttributes() const;

        /**
         * @brief Adds a string attribute to the element.
         * @param attribute the attribute name
         * @param value the string value
         */
        void addStringAttribute(const QString &attribute, const QString &value);

        /**
         * @brief Returns a string attribute value.
         * @param attribute the attribute name
         * @return the string value
         */
        QString getStringAttribute(const QString &attribute) const;

        /**
         * @brief Returns all string attributes.
         * @return the string attributes
         */
        const QMap<QString, QString> &getStringAttributes() const;

        /**
         * @brief Adds a symbolic (discrete) attribute to the element.
         * @param attribute the attribute name
         * @param value the symbolic value
         */
        void addSymbolicAttribute(const QString &attribute, const QString &value);

        /**
         * @brief Returns a symbolic attribute value.
         * @param attribute the attribute name
         * @return the symbolic value
         */
        QString getSymbolicAttribute(const QString &attribute) const;

        /**
         * @brief Returns all symbolic attributes.
         * @return the symbolic attributes
         */
        const QMap<QString, QString> &getSymbolicAttributes() const;

        void print(Printer *p);

    protected:
        /**
         * @brief The type of the element.
         */
        Type type_;

    private:
        /**
         * @brief The creation cost of the element.
         */
        double cost_;

        /**
         * @brief The numeric attributes of the element.
         */
        QMap<QString, double> numericAttributes_;

        /**
         * @brief The string attributes of the element.
         */
        QMap<QString, QString> stringAttributes_;

        /**
         * @brief The symbolic attributes of the element.
         */
        QMap<QString, QString> symbolicAttributes_;
};

#endif /*ELEMENT_H*/
