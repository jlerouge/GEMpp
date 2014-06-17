#ifndef __METADATA_H__
#define __METADATA_H__

#include <QtXml/QtXml>
#include <QMap>
#include <QList>
#include "Weights.h"
#include "../Core/FileStream.h"
#include "../Core/ISaveable.h"

class DLL_EXPORT Metadata : virtual public IPrintable, virtual public ISaveable {
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

        void print(Printer *p);
        void save(const QString &filename);

    protected:
        void fromXML(const QString &filename);
        void toXML();

    private:
        void clean();
        QDomDocument *doc_;
        QMap<QString, QString> graphAttributes_;
        QMap<int, QMap<QString, QString> > verticesAttributes_;
        QMap<int, QMap<QString, QString> > edgesAttributes_;
        QMap<int, QMap<QString, QString> > *attributes[GraphElement::COUNT];
};

#endif /*__METADATA_H__*/
