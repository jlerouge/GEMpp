#include "GraphList.h"

GraphList::GraphList(QDir directory, QString extension) {
    graphs_ = QList<Graph *>();
    //classes_ = QMap< QString, QList<Graph *> >();
    setDir(directory);
    loadGraphs(extension);
}

GraphList::~GraphList() {
    clean();
}

void GraphList::clean() {
    if(!graphs_.isEmpty()) {
        for (auto g : graphs_)
            delete g;
        graphs_.clear();
    }
}

void GraphList::setDir(QDir directory) {
    clean();
    dir_ = directory;
}

int GraphList::getGraphCount() const {
    return graphs_.size();
}

void GraphList::addGraph(Graph *g) {
    if(graphs_.contains(g))
        GEM_exception(QString("GraphList %1 already contains graph %2").arg(dir_.dirName(), g->getID()));
    g->setIndex(graphs_.size());
    graphs_.append(g);
}

Graph *GraphList::getGraph(int i) const {
    return graphs_[i];
}

QList<Graph *>::iterator GraphList::begin() {
    return graphs_.begin();
}

QList<Graph *>::iterator GraphList::end() {
    return graphs_.end();
}

//void GraphList::addGraph(const QString &graphClass, Graph *g) {
//    if(!classes_.contains(graphClass)) {
//        classes_.insert(graphClass, QList<Graph *>());
//    }
//    classes_[graphClass].append(g);
//    addGraph(g);
//}

//Graph *GraphList::getGraph(const QString &graphClass, int i) const {
//    return classes_[graphClass][i];
//}

//int GraphList::getClassCount() const {
//    return classes_.size();
//}

//QList<QString> GraphList::getClasses() const {
//    return classes_.keys();
//}

//int GraphList::getClassSize(const QString &graphClass) const {
//    return classes_[graphClass].size();
//}

void GraphList::print(Printer *p) {
    p->dump(QString("Graph List for directory %1 :").arg(dir_.dirName()));
    p->indent();
    for(auto g : graphs_)
        p->dump(QString("%1").arg(g->getID()));
    p->unindent();
}

void GraphList::loadGraphs(const QString &extension) {
    clean();

    // Looking for graph files recursively
    QStringList sl = QStringList();
    QDirIterator it(dir_.absolutePath(), QDirIterator::Subdirectories);
    while(it.hasNext()) {
        it.next();
        if(!it.fileInfo().isDir()) {
            QString filename = it.filePath();
            if(extension.isEmpty()) {
                if(filename.endsWith(".gxl") || filename.endsWith(".gml"))
                    sl << filename;
            } else {
                if(filename.endsWith(extension))
                    sl << filename;
            }
        }
    }
    // Sort the filenames in the natural order
    std::sort(sl.begin(), sl.end(), compareFileNamesNatural);

    Graph *g;
    // Loading the graphs
    for(auto s : sl) {
        g = new Graph(s);

        //        // Determine the class of the graph with subdirectories
        //        QString graphClass = s;
        //        graphClass.replace(dir_.absolutePath()+"/", "");
        //        QStringList sl = graphClass.split("/");
        //        sl.pop_back();
        //        graphClass = sl.join(".");
        //        if(!graphClass.isEmpty()) {
        //            addGraph(graphClass, g);
        //        } else {
            addGraph(g);
        //}
    }
    qcout << QString("% Loaded %1 graph(s)...").arg(graphs_.size()) << endl;
}

// Credit : http://www.qtcentre.org/threads/21411-QStringList-Sorting
bool compareFileNamesNatural(const QString &s1, const QString &s2) {
    // ignore common prefix..
    int i = 0;
    while ((i < s1.length()) && (i < s2.length()) && (s1.at(i).toLower() == s2.at(i).toLower()))
        ++i;
    ++i;
    // something left to compare?
    if ((i < s1.length()) && (i < s2.length())) {
        // get number prefix from position i - doesnt matter from which string
        int k = i-1;
        //If not number return native comparator
        if(!s1.at(k).isNumber() || !s2.at(k).isNumber()) {
            //Two next lines
            //E.g. 1_... < 12_...
            if(s1.at(k).isNumber())
                return false;
            if(s2.at(k).isNumber())
                return true;
            return QString::compare(s1, s2, Qt::CaseSensitive) < 0;
        }
        QString n = "";
        k--;
        while ((k >= 0) && (s1.at(k).isNumber())) {
            n = s1.at(k)+n;
            --k;
        }
        // get relevant/signficant number string for s1
        k = i-1;
        QString n1 = "";
        while ((k < s1.length()) && (s1.at(k).isNumber())) {
            n1 += s1.at(k);
            ++k;
        }

        // get relevant/signficant number string for s2
        //Decrease by
        k = i-1;
        QString n2 = "";
        while ((k < s2.length()) && (s2.at(k).isNumber())) {
            n2 += s2.at(k);
            ++k;
        }

        // got two numbers to compare?
        if (!n1.isEmpty() && !n2.isEmpty())
            return (n+n1).toInt() < (n+n2).toInt();
        else {
            // not a number has to win over a number.. number could have ended earlier... same prefix..
            if (!n1.isEmpty())
                return false;
            if (!n2.isEmpty())
                return true;
            return s1.at(i) < s2.at(i);
        }
    } else {
        // shortest string wins
        return s1.length() < s2.length();
    }
}
