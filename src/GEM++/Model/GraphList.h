#ifndef __GRAPHLIST_H__
#define __GRAPHLIST_H__

#include <QDirIterator>
#include "Graph.h"
#include "../Core/ICleanable.h"

class DLL_EXPORT GraphList : virtual public IPrintable, virtual public ICleanable {
    public:
        GraphList(QDir directory, QString extension = "");
        virtual ~GraphList();

        int getGraphCount() const;
        void setDir(QDir directory);
        void addGraph(Graph *g);
        Graph *getGraph(int i) const;
        void loadGraphs(const QString &extension = "");

        QList<Graph *>::iterator begin();
        QList<Graph *>::iterator end();

        //        void addGraph(const QString &graphClass, Graph *g);
        //        Graph *getGraph(const QString &graphClass, int i) const;
        //        int getClassCount() const;
        //        QList<QString> getClasses() const;
        //        int getClassSize(const QString &graphClass) const;

        virtual void print(Printer *p);
        virtual void clean();

    private:
        QDir dir_;
        QList<Graph *> graphs_;
        //QMap< QString, QList<Graph *> > classes_;
};

bool compareFileNamesNatural(const QString &s1, const QString &s2);

#endif /*__GRAPH_H__*/
