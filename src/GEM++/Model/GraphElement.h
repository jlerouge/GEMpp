#ifndef __GRAPHELEMENT_H__
#define __GRAPHELEMENT_H__

#include <QMap>
#include "../Core/IPrintable.h"
#include "../Core/Identified.h"
#include "../Core/Indexed.h"

class DLL_EXPORT GraphElement : virtual public IPrintable, virtual public Identified, virtual public Indexed {
        friend class Vertex;
        friend class Edge;
    public:
        enum Type{
            VERTEX = 0,
            EDGE,
            COUNT
        };

        static const char *typeName[COUNT];
        static QString toName(Type type);
        static Type fromName(QString tName);

        GraphElement();
        GraphElement(const GraphElement &other);
        virtual ~GraphElement();

        double getCost() const;
        void setCost(double d);
        Type getType() const;

        void addNumericAttribute(const QString &attribute, double value);
        double getNumericAttribute(QString attribute) const;
        const QMap<QString, double> &getNumericAttributes() const;

        void addStringAttribute(const QString &attribute, const QString &value);
        QString getStringAttribute(const QString &attribute) const;
        const QMap<QString, QString> &getStringAttributes() const;

        void addSymbolicAttribute(const QString &attribute, const QString &value);
        QString getSymbolicAttribute(const QString &attribute) const;
        const QMap<QString, QString> &getSymbolicAttributes() const;

        void print(Printer *p);

    protected:
        Type type_;

    private:
        double cost_;
        QMap<QString, double> numericAttributes_;
        QMap<QString, QString> stringAttributes_;
        QMap<QString, QString> symbolicAttributes_;
};

#endif /*__ELEMENT_H__*/
