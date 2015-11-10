#include "Graph.h"

const char *Graph::typeName[Graph::COUNT] = {
    "directed",
    "undirected"
};

Graph::Type Graph::fromName(QString name) {
    for(Type t = (Type)0; t < COUNT; t = (Type)((int)t + 1))
        if(QString(typeName[t]).startsWith(name, Qt::CaseInsensitive))
            return t;
    Exception(QString("Graph type '%1' not recognized, please use d(irected) or u(ndirected).").arg(name));
    return COUNT;
}

QString Graph::toName(Type type) {
    return typeName[type];
}

Graph::Graph(Type type) : Identified(), Indexed() {
    type_ = type;
    metadata_ = new Metadata();
}

Graph::Graph(const QString &filename) : Graph() {
    fromFile(filename);
}

Graph::~Graph() {
    for(auto it: vertices_)
        delete it;
    for(auto it: edges_)
        delete it;
}

const QList <Vertex *> &Graph::getVertices() const {
    return vertices_;
}

Vertex *Graph::getVertex(int i) const {
    return vertices_[i];
}

void Graph::addVertex(Vertex *v, QString id) {
    v->setIndex(vertices_.size());
    QString sid = !id.isEmpty()? id : QString::number(vertices_.size());
    if(v->getID().isEmpty())
        v->setID(sid);
    verticesInsertionOrder_.insert(sid,vertices_.size());
    vertices_.push_back(v);
}

void Graph::removeVertex(Vertex *v) {
    int index = v->getIndex();
    QString key;
    if(vertices_[index] != v)
        Exception(QString("Index mismatch in vertices of the graph %1").arg(id_));

    // Remove the references
    vertices_.removeAt(index);
    verticesInsertionOrder_.remove(verticesInsertionOrder_.key(index));

    // Reindex the vertices
    for(int i=index; i < vertices_.size(); ++i) {
        vertices_[i]->setIndex(i);
        key = verticesInsertionOrder_.key(i+1);
        verticesInsertionOrder_[key] = i;
    }

    // Remove the incident edges
    for(auto e: v->getEdges(Vertex::EDGE_IN_OUT))
        removeEdge(e);
}

const QList <Edge *> &Graph::getEdges() const {
    return edges_;
}

Edge *Graph::getEdge(int i) const {
    return edges_[i];
}

void Graph::addEdge(Edge *e) {
    e->setIndex(edges_.size());
    edges_.push_back(e);
}

void Graph::removeEdge(Edge *e) {
    int index = e->getIndex();
    if(edges_[index] != e)
        Exception(QString("Index mismatch in edges of the graph %1").arg(id_));
    edges_.removeAt(index);
    e->getOrigin()->removeEdge(e);
    e->getTarget()->removeEdge(e);
}

Metadata *Graph::getMetadata() const {
    return metadata_;
}

int Graph::getVertexCount() const {
    return vertices_.size();
}

int Graph::getEdgeCount() const {
    return edges_.size();
}

Graph::Type Graph::getType() const {
    return type_;
}

void Graph::setType(Type type) {
    type_ = type;
}

Graph *Graph::neighborhoodSubgraph(int iSeed, int nbhdSize) {
    QSet<Vertex *> seeds;
    seeds.insert(getVertex(iSeed));
    return neighborhoodSubgraphRec(seeds, nbhdSize);
}

Graph *Graph::neighborhoodSubgraph(QSet<int> iSeeds, int nbhdSize) {
    QSet<Vertex *> seeds;
    for(auto i: iSeeds)
        seeds.insert(getVertex(i));
    return neighborhoodSubgraphRec(seeds, nbhdSize);
}

Graph *Graph::neighborhoodSubgraphRec(QSet<Vertex *> vertices, int nbhdSize) {
    if(nbhdSize <= 0)
        return generateInducedSubgraph(vertices);

    QList<Vertex *> temp;
    for(auto v: vertices) {
        for(auto e: v->getEdges(Vertex::EDGE_OUT))
            temp.push_back(e->getTarget());
        for(auto e: v->getEdges(Vertex::EDGE_IN))
            temp.push_back(e->getOrigin());
    }
    for(auto v: temp)
        vertices.insert(v);
    return neighborhoodSubgraphRec(vertices, nbhdSize - 1);
}

Graph *Graph::randomSubgraph(int iSeed, int vCount) {
    QSet<Vertex *> vertices = QSet<Vertex *>();
    QSet<Vertex *> neighbours = QSet<Vertex *>();
    Vertex *v = 0;

    for(int k=0; k < vCount; ++k) {
        if(k == 0) {
            v = getVertex(iSeed);
        } else if(!neighbours.isEmpty()) {
            v = neighbours.toList()[Random::randInt(0, neighbours.size()-1)];
        } else {
            break;
        }
        vertices.insert(v);
        for(auto e: v->getEdges(Vertex::EDGE_OUT))
            neighbours.insert(e->getTarget());
        for(auto e: v->getEdges(Vertex::EDGE_IN))
            neighbours.insert(e->getOrigin());
        for(auto v: vertices)
            neighbours.remove(v);
    }
    return generateInducedSubgraph(vertices);
}


Graph *Graph::generateInducedSubgraph(const QSet<Vertex *> &vertices) {
    Graph *subgraph = new Graph(type_);
    QList<Vertex *> vList = vertices.toList();
    QList<Edge *> eList = QList<Edge *>();
    Edge *newE = 0;

    // Copy vertices
    for(auto v: vList)
        subgraph->addVertex(new Vertex(*v), v->getID());

    // Copy edges and resets their origins and targets
    for(auto e: edges_) {
        if(vertices.contains(e->getOrigin()) &&  vertices.contains(e->getTarget())) {
            subgraph->addEdge(newE = new Edge(*e));
            newE->setOrigin(subgraph->getVertex(vList.indexOf(e->getOrigin())));
            newE->setTarget(subgraph->getVertex(vList.indexOf(e->getTarget())));
            eList.append(e);
        }
    }

    // Resets the incident edges of vertices
    for(auto v: subgraph->getVertices()) {
        for(auto e: v->getEdges(Vertex::EDGE_IN)) {
            v->removeEdge(e);
            if(eList.contains(e))
                v->addEdge(subgraph->getEdge(eList.indexOf(e)), Vertex::EDGE_IN);
        }
        for(auto e: v->getEdges(Vertex::EDGE_OUT)) {
            v->removeEdge(e);
            if(eList.contains(e))
                v->addEdge(subgraph->getEdge(eList.indexOf(e)), Vertex::EDGE_OUT);
        }
    }

    int pIndex = 0;
    // Copy graph metadata
    for(auto key : metadata_->getGraphAttributes().keys())
        subgraph->getMetadata()->setGraphAttribute(key, metadata_->getGraphAttribute(key));

    // Copy vertex metadata
    for(int i=0; i < subgraph->getVertexCount(); ++i) {
        pIndex = vList[i]->getIndex();
        for(auto key : metadata_->getAttributes(GraphElement::VERTEX, pIndex).keys())
            subgraph->getMetadata()->setAttribute(GraphElement::VERTEX, i, key, metadata_->getAttribute(GraphElement::VERTEX, pIndex, key));
    }

    // Copy edge metadata
    for(int ij=0; ij < subgraph->getEdgeCount(); ++ij) {
        pIndex = eList[ij]->getIndex();
        for(auto key : metadata_->getAttributes(GraphElement::EDGE, pIndex).keys())
            subgraph->getMetadata()->setAttribute(GraphElement::EDGE, ij, key, metadata_->getAttribute(GraphElement::EDGE, pIndex, key));
    }

    return subgraph;
}

void Graph::fromFile(const QString &filename) {
    if(filename.endsWith(".gml", Qt::CaseInsensitive))
        fromGML(filename);
    else if(filename.endsWith(".gxl", Qt::CaseInsensitive))
        fromGXL(filename);
    else if(filename.endsWith(".xml", Qt::CaseInsensitive))
        fromXML(filename);
    else
        Exception(QString("%1 is not a *.gml, *.gxl nor *.xml file.").arg(filename));
    id_ = QFileInfo(filename).completeBaseName();
}

void Graph::fromGML(const QString &filename) {
    QString buffer = FileUtils::load(filename);
    QRegExp directed = QRegExp("directed (0|1)");
    QRegExp vertex_begin = QRegExp("node \\[");
    QRegExp edge_begin = QRegExp("edge \\[");
    QRegExp group_end = QRegExp("\\]");
    QString id;
    QString label;
    Vertex *v = 0;
    Edge *e = 0;

    // Graph type
    int begin = directed.indexIn(buffer), end;
    QStringList sl = buffer.mid(begin, directed.matchedLength()).simplified().split(" ");
    type_ = (sl[1].toInt())? DIRECTED : UNDIRECTED;

    // Parse vertices
    begin = 0;
    begin = vertex_begin.indexIn(buffer);
    begin += vertex_begin.matchedLength();
    end = group_end.indexIn(buffer, begin);
    while(begin >= 0) {
        v = new Vertex();
        label = "";
        sl = buffer.mid(begin, end-begin).simplified().split(" ");
        if(sl.size() > 1) {
            for(auto it = sl.begin(); it != sl.end(); it += 2) {
                if(it == sl.end()) break;
                if(!it->compare("id", Qt::CaseInsensitive)) {
                    id = *(it+1);
                } else if(!it->compare("label", Qt::CaseInsensitive)) {
                    label = (it+1)->remove('\"');
                } else if(it->compare("comment", Qt::CaseInsensitive)) {
                    if((it+1)->contains('\"'))
                        v->addSymbolicAttribute(*it, (it+1)->remove('\"'));
                    else
                        v->addNumericAttribute(*it, (it+1)->toDouble());
                }
            }
        }
        if(!label.isEmpty())
            v->setID(label);
        addVertex(v, id);

        // Prepare next iteration
        begin = vertex_begin.indexIn(buffer, begin);
        begin += vertex_begin.matchedLength();
        end = group_end.indexIn(buffer, begin);
    }

    // Parse edges
    begin = 0;
    begin = edge_begin.indexIn(buffer);
    begin += edge_begin.matchedLength();
    end = group_end.indexIn(buffer, begin);
    while(begin >= 0) {
        sl = buffer.mid(begin, end-begin).simplified().split(" ");
        if(sl.size() > 1) {
            e = new Edge();
            label = "";
            for(auto it = sl.begin(); it != sl.end(); it += 2) {
                if(it == sl.end()) break;
                if(it->compare("source", Qt::CaseInsensitive) == 0) {
                    id = *(it+1);
                    e->setOrigin(vertices_[verticesInsertionOrder_[id]]);
                } else if(it->compare("target", Qt::CaseInsensitive) == 0) {
                    id = *(it+1);
                    e->setTarget(vertices_[verticesInsertionOrder_[id]]);
                } else if(!it->compare("label", Qt::CaseInsensitive)) {
                    label = (it+1)->remove('\"');
                } else if(it->compare("comment", Qt::CaseInsensitive)) {
                    if((it+1)->contains('\"'))
                        e->addSymbolicAttribute(*it, (it+1)->remove('\"'));
                    else
                        e->addNumericAttribute(*it, (it+1)->toDouble());
                }
            }
        }
        if(!label.isEmpty())
            e->setID(label);
        // e may be deleted
        addEdge(e);
        e = edges_.last();
        e->getOrigin()->addEdge(e, Vertex::EDGE_OUT);
        e->getTarget()->addEdge(e, Vertex::EDGE_IN);
        // Prepare next iteration
        begin = edge_begin.indexIn(buffer, begin);
        begin += edge_begin.matchedLength();
        end = group_end.indexIn(buffer, begin);
    }
}

void Graph::fromGXL(const QString &filename) {
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
        Exception(QString("Error while loading %1").arg(filename, file.errorString()));

    QDomDocument doc;
    doc.setContent(&file, false);
    QDomElement graph = doc.documentElement().firstChildElement("graph");

    // Graph type
    type_ = (Type)(!graph.attribute("edgemode").compare("undirected", Qt::CaseInsensitive));

    // Edges have id's
    bool edgeids = !graph.attribute("edgeids", "false").compare("true", Qt::CaseInsensitive);

    // Parse vertices
    Vertex *v;
    QString attrType;
    QDomElement elem = graph.firstChildElement("node");
    QDomElement attr;
    while (!elem.isNull())
    {
        v = new Vertex();
        attr = elem.firstChildElement("attr");
        while(!attr.isNull()) {
            attrType = attr.firstChildElement().tagName();
            if(attrType.compare("integer", Qt::CaseInsensitive) == 0 ||
                    attrType.compare("float", Qt::CaseInsensitive) == 0)
                v->addNumericAttribute(attr.attribute("name"), attr.firstChildElement().text().toDouble());
            else if(attrType.compare("string", Qt::CaseInsensitive) == 0)
                v->addSymbolicAttribute(attr.attribute("name"), attr.firstChildElement().text());
            attr = attr.nextSiblingElement("attr");
        }
        addVertex(v, elem.attribute("id"));
        elem = elem.nextSiblingElement("node");
    }

    // Parse edges
    elem = graph.firstChildElement("edge");
    Edge *e;
    while(!elem.isNull()) {
        e = new Edge();
        if(edgeids)
            e->setID(graph.attribute("id", QString("e%1").arg(e->getIndex())));
        e->setOrigin(vertices_[verticesInsertionOrder_[elem.attribute("from")]]);
        e->setTarget(vertices_[verticesInsertionOrder_[elem.attribute("to")]]);
        attr = elem.firstChildElement("attr");
        while(!attr.isNull()) {
            attrType = attr.firstChildElement().tagName();
            if(attrType.compare("integer", Qt::CaseInsensitive) == 0 ||
                    attrType.compare("float", Qt::CaseInsensitive) == 0)
                e->addNumericAttribute(attr.attribute("name"), attr.firstChildElement().text().toDouble());
            else if(attrType.compare("string", Qt::CaseInsensitive) == 0)
                e->addSymbolicAttribute(attr.attribute("name"), attr.firstChildElement().text());
            attr = attr.nextSiblingElement("attr");
        }
        addEdge(e);
        // e may be deleted
        e = edges_.last();
        e->getOrigin()->addEdge(e, Vertex::EDGE_OUT);
        e->getTarget()->addEdge(e, Vertex::EDGE_IN);
        elem = elem.nextSiblingElement("edge");
    }
    file.close();
}

void Graph::fromXML(const QString &filename) {
    metadata_->fromXML(filename);
    QString path = QFileInfo(filename).path();
    fromFile(path+"/"+metadata_->getGraphAttribute("graphfile").toString());
}

void Graph::print(Printer *p) {
    // FIXME : gxl ?
    p->dump("graph [");
    p->indent();
    p->dump(QString("directed %1").arg(type_ == DIRECTED));
    // Vertices
    for(auto v : vertices_) {
        p->dump("node [");
        p->indent();
        p->dump(QString("id %1").arg(v->getIndex()));
        p->dump(QString("label \"%1\"").arg(v->getID()));
        for(auto att : v->getNumericAttributes().keys())
            p->dump(QString("%1 %2").arg(att).arg(v->getNumericAttribute(att)));
        for(auto att : v->getStringAttributes().keys())
            p->dump(QString("%1 \"%2\"").arg(att).arg(v->getStringAttribute(att)));
        for(auto att : v->getSymbolicAttributes().keys())
            p->dump(QString("%1 \"%2\"").arg(att).arg(v->getSymbolicAttribute(att)));
        p->unindent();
        p->dump("]");
    }
    // Edges
    for(auto e : edges_) {
        p->dump("edge [");
        p->indent();
        p->dump(QString("source %1").arg(e->getOrigin()->getIndex()));
        p->dump(QString("target %1").arg(e->getTarget()->getIndex()));
        for(auto att : e->getNumericAttributes().keys())
            p->dump(QString("%1 %2").arg(att).arg(e->getNumericAttribute(att)));
        for(auto att : e->getStringAttributes().keys())
            p->dump(QString("%1 \"%2\"").arg(att).arg(e->getStringAttribute(att)));
        for(auto att : e->getSymbolicAttributes().keys())
            p->dump(QString("%1 \"%2\"").arg(att).arg(e->getSymbolicAttribute(att)));
        p->unindent();
        p->dump("]");
    }
    p->unindent();
    p->dump("]");
}

void Graph::save(const QString &filename) {
    FileUtils::save(this, filename);
}
