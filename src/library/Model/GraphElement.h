#ifndef GEMPP_GRAPHELEMENT_H
#define GEMPP_GRAPHELEMENT_H

#include <QMap>
#include "Attribute.h"
#include "Core/IPrintable.h"
#include "Core/Identified.h"
#include "Core/Indexed.h"
#include "Core/IXmlElementSerializable.h"

class Graph;

/**
 * @brief The GraphElement class represents an abstract element of a ::Graph, i.e. a ::Vertex or an ::Edge.
 * A ::Graph may also be a particular ::Vertex of a parent ::Graph, the latter being a hierarchical graph.
 * These elements have attributes, and it is possible to compute substitution costs between two ::GraphElement
 * of the same type as well as the creation cost of a single ::GraphElement, using the substitution and creation
 * ::Weights.
 * @see Edge
 * @see Vertex
 * @see Graph
 * @see Weights
 */
class DLL_EXPORT GraphElement : virtual public IPrintable, virtual public IXmlElementSerializable, virtual public Identified, virtual public Indexed {
    public:
        /**
         * @brief Indicates the type of the GraphElement.
         */
        enum Type{
            GRAPH = 0,  /**< a ::Graph */
            VERTEX,     /**< a ::Vertex */
            EDGE,       /**< an ::Edge */
            COUNT       /**< used to iterate on GraphElement::Type enum */
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
        static Type toType(QString name);

        /**
         * @brief Constructs a new GraphElement object.
         */
        GraphElement(Type type = COUNT);

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
         * @brief Sets the type of this element.
         * @param type the type
         */
        void setType(Type type);

        /**
         * @brief Adds an attribute to the element.
         * @param name the attribute name
         * @param type the type of the attribute
         * @param value the value
         */
        void addAttribute(const QString &name, QMetaType::Type type, QVariant value);

        /**
         * @brief Adds an attribute to the element.
         * @param name the attribute name
         * @param attribute the attribute
         */
        void addAttribute(const QString &name, Attribute *attribute);

        /**
         * @brief Indicates whether the element has a particular attribute.
         * @param name the attribute name
         * @return a boolean
         */
        bool hasAttribute(const QString &name) const;

        /**
         * @brief Returns an attribute of the element.
         * @param name the attribute name
         * @return the attribute
         * @warning throws an Exception if the attribute does not exist
         */
        Attribute *getAttribute(const QString &name) const;

        /**
         * @brief Returns all attributes of the element.
         * @return the attributes
         */
        const QMap<QString, Attribute *> &getAttributes() const;

        /**
         * @brief Returns the ::Graph represented by this ::GraphElement.
         * @return a ::Graph
         */
        Graph *getGraph() const;

        /**
         * @brief Sets the ::Graph represented by this ::GraphElement.
         * @param graph a ::Graph
         */
        void setGraph(Graph *graph);

        /**
         * @brief Prints the element id to a printer.
         * @param p the printer
         */
        virtual void print(Printer *p);

        /**
         * @brief Serializes the object to an XML element in the GXL format.
         * @param document the root XML document
         * @return the XML element
         */
        virtual QDomElement save(QDomDocument *document);

        /**
         * @brief Deserializes the object from an XML element in the GXL format.
         * @param element the XML element
         */
        virtual void load(QDomElement element);

    private:
        /**
         * @brief The type of the element.
         */
        Type type_;

        /**
         * @brief The creation cost of the element.
         */
        double cost_;

        /**
         * @brief The attributes of the element.
         */
        QMap<QString, Attribute *> attributes_;

        /**
         * @brief A subgraph represented by a ::Vertex of the parent ::Graph.
         * This allows to construct hierarchical graphs.
         */
        Graph *graph_;
};

#endif /* GEMPP_GRAPHELEMENT_H */
