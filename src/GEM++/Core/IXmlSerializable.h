#ifndef __IXMLSERIALIZABLE_H__
#define __IXMLSERIALIZABLE_H__

#include <QtXml/QtXml>
#include "FileStream.h"
#include "ISaveable.h"
#include "ICleanable.h"

/**
 * @brief The IXmlSerializable class is an interface for objects that are serializable in XML format.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT IXmlSerializable : virtual public IPrintable, virtual public ISaveable, virtual public ICleanable {
    public:
        /**
         * @brief Constructs a new IXmlSerializable object.
         */
        IXmlSerializable() : doc_(0) {}

        /**
         * @brief Destructs an IXmlSerializable object.
         */
        virtual ~IXmlSerializable() {
            clean();
        }

        /**
         * @brief Prints the content of the IXmlSerializable object.
         * @param p the Printer
         */
        virtual void print(Printer *p) {
            toXML();
            p->dump("<?xml version=\"1.0\"?>");
            p->dump(doc_->toString(p->getIndentWidth()));
        }

        /**
         * @brief Saves the content of the IXmlSerializable object.
         * @param filename the path to the saved file
         */
        virtual void save(const QString &filename) {
            FileStream::saveFile(this, filename);
        }

        /**
         * @brief Cleans the IXmlSerializable object.
         */
        virtual void clean() {
            if(doc_)
                delete doc_;
            doc_ = 0;
        }

        /**
         * @brief The DOM document used to serialize the object before saving.
         */
        QDomDocument *doc_;

    protected:
        /**
         * @brief Deserializes an object from an XML file.
         * @param filename the path to the XML file
         */
        virtual void fromXML(const QString &filename) = 0;

        /**
         * @brief Serializes an object to a QDomDocument.
         */
        virtual void toXML() = 0;
};

#endif /*__IXMLSERIALIZABLE_H__*/
