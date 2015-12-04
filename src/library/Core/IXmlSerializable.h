#ifndef GEMPP_IXMLSERIALIZABLE_H
#define GEMPP_IXMLSERIALIZABLE_H

#include <QtXml/QtXml>
#include "FileUtils.h"
#include "ILoadable.h"
#include "ISaveable.h"
#include "ICleanable.h"

/**
 * @brief The IXmlSerializable class is an interface for objects
 * that can be serialized to files in XML format.
 * @see QDomDocument
 * @warning This interface must be implemented to be used.
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT IXmlSerializable : virtual public ILoadable, virtual public ISaveable, virtual public ICleanable {
    public:
        /**
         * @brief Constructs a new IXmlSerializable object.
         */
        IXmlSerializable();

        /**
         * @brief Destructs an IXmlSerializable object.
         */
        virtual ~IXmlSerializable();

        /**
         * @brief Returns the XML filename to which the object is serialized.
         * @return the value of IXMLSerializable::filename_
         */
        QString getFilename() const;

        /**
         * @brief Sets the XML filename to which the object is serialized.
         * @param filename the new XML filename of the IXMLSerializable
         */
        void setFilename(const QString &filename);

        /**
         * @brief Deserializes the object from an XML document.
         * @param filename the XML file to be read
         * @see IXmlSerializable::fromXML()
         */
        virtual void load(const QString &filename = QString());

        /**
         * @brief Serializes the object to an XML document.
         * @param filename the XML file to be written
         * @see IXmlSerializable::toXML()
         */
        virtual void save(const QString &filename = QString());

        void clean();

    protected:
        /**
         * @brief Implements the deserialization. The XML document
         * can be accessed using IXmlSerializable::document() function.
         * @see IXmlSerializable::load(), IXmlSerializable::document()
         * @warning this function must be implemented in the derived class
         */
        virtual void fromXML() = 0;

        /**
         * @brief Implements the serialization. The XML document
         * can be accessed using IXmlSerializable::document() function.
         * @see IXmlSerializable::save(), IXmlSerializable::document()
         * @warning this function must be implemented in the derived class
         */
        virtual void toXML() = 0;

        /**
         * @brief Returns the XML document to be read or written.
         * @return the value of IXmlSerializable::doc_
         */
        QDomDocument *document() const;

    private:
        /**
         * @brief The XML document to be read or written.
         */
        QDomDocument *doc_;

        /**
         * @brief The XML filename to which the object is serialized.
         */
        QString filename_;
};

#endif /* GEMPP_IXMLSERIALIZABLE_H */
