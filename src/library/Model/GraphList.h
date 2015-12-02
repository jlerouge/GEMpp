#ifndef GEMPP_GRAPHLIST_H
#define GEMPP_GRAPHLIST_H

#include <QDirIterator>
#include "Graph.h"
#include "Core/ICleanable.h"

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

        virtual void print(Printer *p);
        virtual void clean();

    private:
        QDir dir_;
        QList<Graph *> graphs_;
};

bool compareFileNamesNatural(const QString &s1, const QString &s2);

#endif /* GEMPP_GRAPHLIST_H */
