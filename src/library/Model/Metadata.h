#ifndef GEMPP_METADATA_H
#define GEMPP_METADATA_H

#include <QtXml/QtXml>
#include <QMap>
#include <QList>
#include "GraphElement.h"
#include "Core/IXmlSerializable.h"

class DLL_EXPORT Metadata : virtual public IXmlSerializable {
        friend class Graph;
    public:
        Metadata();
        Metadata(const QString &filename);
        virtual ~Metadata();

        QVariant getGraphAttribute(QString name) const;
        void setGraphAttribute(QString name, QVariant value);
        const QMap<QString, QString> &getGraphAttributes() const;

        QVariant getAttribute(GraphElement::Type type, uint index, QString name) const;
        void setAttribute(GraphElement::Type type, uint index, QString name, QVariant value);
        const QMap<QString, QString> getAttributes(GraphElement::Type type, uint index) const;

    protected:
        virtual void fromXML();
        virtual void toXML();

    private:
        QMap<QString, QString> graphAttributes_;
        QMap<int, QMap<QString, QString> > verticesAttributes_;
        QMap<int, QMap<QString, QString> > edgesAttributes_;
        QMap<int, QMap<QString, QString> > *attributes[GraphElement::COUNT];
};

#endif /* GEMPP_METADATA_H */
