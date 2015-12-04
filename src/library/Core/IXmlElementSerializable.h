#ifndef GEMPP_IXMLELEMENTSERIALIZABLE_H
#define GEMPP_IXMLELEMENTSERIALIZABLE_H

#include <QtXml/QtXml>
#include "Portability.h"

/**
 * @brief The IXmlElementSerializable class is an interface for objects
 * that can be serialized to XML elements.
 * @see QDomElement
 * @see IXmlSerializable
 * @warning This interface must be implemented to be used.
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT IXmlElementSerializable {
    public:
        /**
         * @brief Destructs an IXmlElementSerializable object.
         */
        virtual ~IXmlElementSerializable() {}

    protected:
        /**
         * @brief Serializes the object to an XML element.
         * @param document the root XML document
         * @return the XML element
         * @warning this function must be implemented in the derived class
         */
        virtual QDomElement save(QDomDocument *document) = 0;

        /**
         * @brief Deserializes the object from an XML element.
         * @param element the XML element
         * @warning this function must be implemented in the derived class
         */
        virtual void load(QDomElement element) = 0;
};

#endif /* GEMPP_IXMLELEMENTSERIALIZABLE_H */
