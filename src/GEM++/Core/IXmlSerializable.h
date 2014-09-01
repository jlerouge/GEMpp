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

        virtual void print(Printer *p) {
            toXML();
            p->dump("<?xml version=\"1.0\"?>");
            p->dump(doc_->toString(p->getIndentWidth()));
        }

        virtual void save(const QString &filename) {
            FileStream::saveFile(this, filename);
        }

        virtual void clean() {
            if(doc_)
                delete doc_;
            doc_ = 0;
        }

        QDomDocument *doc_;

    protected:
        virtual void fromXML(const QString &filename) = 0;
        virtual void toXML() = 0;
};

#endif /*__IXMLSERIALIZABLE_H__*/
