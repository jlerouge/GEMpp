#include "Graph.h"

const char *Graph::typeName[Graph::TYPE_COUNT] = {
    "directed",
    "undirected"
};

Graph::Type Graph::toType(QString name) {
    for(Type t = (Type)0; t < TYPE_COUNT; t = (Type)((int)t + 1))
        if(QString(typeName[t]).startsWith(name, Qt::CaseInsensitive))
            return t;
    Exception(QString("Graph type '%1' not recognized, please use d(irected) or u(ndirected).").arg(name));
    return TYPE_COUNT;
}

QString Graph::toName(Type type) {
    return typeName[type];
}

const char *Graph::formatName[Graph::FORMAT_COUNT] = {
    "gml",
    "gxl",
    "xml"
};

Graph::Format Graph::toFormat(QString name) {
    for(Format t = (Format)0; t < FORMAT_COUNT; t = (Format)((int)t + 1))
        if(QString(formatName[t]).startsWith(name, Qt::CaseInsensitive))
            return t;
    Exception(QString("Graph format '%1' not recognized, please use gml, gxl or xml.").arg(name));
    return FORMAT_COUNT;
}

QString Graph::toName(Format format) {
    return formatName[format];
}

Graph::Graph(Type type): GraphElement(GraphElement::GRAPH) {
    type_ = type;
    metadata_ = new Metadata();
}

Graph::Graph(const QString &filename) : Graph() {
    load(filename);
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

QList<GraphElement *> Graph::getTerminals(GraphElement::Type type) const {
    QList<GraphElement *> result;
    if(type == GraphElement::VERTEX || type == GraphElement::COUNT) {
        for(auto v : vertices_) {
            if(v->getGraph())
                result.append(v->getGraph()->getTerminals(type));
            else
                result.append(v);
        }
    }
    if(type == GraphElement::EDGE || type == GraphElement::COUNT) {
        for(auto e : edges_) {
            if(e->getGraph())
                result.append(e->getGraph()->getTerminals(type));
            else
                result.append(e);
        }
    }
    return result;
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

void Graph::removeVertex(QString id) {
    removeVertex(verticesInsertionOrder_[id]);
}

void Graph::removeVertex(int index) {
    removeVertex(vertices_[index]);
}

void Graph::removeVertex(Vertex *v) {
    int index = v->getIndex();
    QString key;
    if(vertices_[index] != v)
        Exception(QString("Index mismatch in vertices of the graph %1").arg(getID()));

    // Remove the references
    vertices_.removeAt(index);
    verticesInsertionOrder_.remove(verticesInsertionOrder_.key(index));

    // Reindex the vertices
    for(int i=index; i < vertices_.size(); ++i) {
        vertices_[i]->setIndex(i);
        key = verticesInsertionOrder_.key(i+1);
        verticesInsertionOrder_[key] = i;
    }
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

void Graph::removeEdge(int index) {
    removeEdge(edges_[index]);
}

void Graph::removeEdge(Edge *e) {
    int index = e->getIndex();
    if(edges_[index] != e)
        Exception(QString("Index mismatch in edges of the graph %1").arg(getID()));

    // Remove the references
    edges_.removeAt(index);
    e->getOrigin()->removeEdge(e);
    e->getTarget()->removeEdge(e);

    // Reindex the edges
    for(int i=index; i < edges_.size(); ++i)
        edges_[i]->setIndex(i);
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

void Graph::computeCosts(Weights *weights) {
    double total = 0;

    // Vertices creations costs
    for(auto v : vertices_) {
        if(v->getGraph()) {
            v->getGraph()->computeCosts(weights);
            v->setCost(v->getGraph()->getCost());
        } else {
            v->setCost(weights->creationCost(v));
        }
        total += v->getCost();
    }

    // Edges creations costs
    for(auto e : edges_) {
        e->setCost(weights->creationCost(e));
        total += e->getCost();
    }

    // Total cost
    setCost(total);
}

Graph *Graph::copy() const {
    return inducedSubgraph(vertices_.toSet());
}

Graph *Graph::neighborhoodSubgraph(int iSeed, int nbhdSize) const {
    QSet<Vertex *> seeds;
    seeds.insert(getVertex(iSeed));
    return neighborhoodSubgraphRec(seeds, nbhdSize);
}

Graph *Graph::neighborhoodSubgraph(QSet<int> iSeeds, int nbhdSize) const {
    QSet<Vertex *> seeds;
    for(auto i: iSeeds)
        seeds.insert(getVertex(i));
    return neighborhoodSubgraphRec(seeds, nbhdSize);
}

Graph *Graph::neighborhoodSubgraphRec(QSet<Vertex *> vertices, int nbhdSize) const {
    if(nbhdSize <= 0)
        return inducedSubgraph(vertices);

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

Graph *Graph::randomSubgraph(int iSeed, int vCount) const {
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
    return inducedSubgraph(vertices);
}


Graph *Graph::inducedSubgraph(const QSet<Vertex *> &vertices) const {
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
        try {
            for(auto key : metadata_->getAttributes(GraphElement::VERTEX, pIndex).keys())
                subgraph->getMetadata()->setAttribute(GraphElement::VERTEX, i, key, metadata_->getAttribute(GraphElement::VERTEX, pIndex, key));
        } catch (std::exception &e) {}
    }

    // Copy edge metadata
    for(int ij=0; ij < subgraph->getEdgeCount(); ++ij) {
        pIndex = eList[ij]->getIndex();
        try {
            for(auto key : metadata_->getAttributes(GraphElement::EDGE, pIndex).keys())
                subgraph->getMetadata()->setAttribute(GraphElement::EDGE, ij, key, metadata_->getAttribute(GraphElement::EDGE, pIndex, key));
        } catch (std::exception &e) {}
    }

    return subgraph;
}

void Graph::load(const QString &filename) {
    Format format = toFormat(FileUtils::getExtension(filename));
    switch(format) {
        case GML:
            fromGML(filename);
            break;
        case GXL:
            IXmlSerializable::load(filename);
            break;
        case XML:
            fromXMLMetadata(filename);
            break;
        default:
            Exception(QString("%1 is not a *.gml, *.gxl nor *.xml file.").arg(filename));
            break;
    }
    if(getID().isEmpty())
        setID(QFileInfo(filename).completeBaseName());
}

void Graph::save(const QString &filename) {
    Format format = toFormat(FileUtils::getExtension(filename));
    switch(format) {
        case GML:
            toGML(filename);
            break;
        case GXL:
            IXmlSerializable::save(filename);
            break;
        case XML:
            toXMLMetadata(filename);
            break;
        default:
            Exception(QString("%1 is not a *.gml, *.gxl nor *.xml file.").arg(filename));
            break;
    }
}

void Graph::load(QDomElement element) {
    GraphElement::load(element);
    if(element.hasAttribute("id"))
        setID(element.attribute("id"));

    QString graphTag = GraphElement::toName(GraphElement::GRAPH);
    QString vertexTag = GraphElement::toName(GraphElement::VERTEX);
    QString edgeTag = GraphElement::toName(GraphElement::EDGE);

    type_ = toType(element.attribute("edgemode"));
    bool edgeids = Attribute::toVariant(QMetaType::Bool, element.attribute("edgeids", "false")).toBool();

    // Parse vertices
    Vertex *v;
    Graph *g;
    QDomElement elem = element.firstChildElement(vertexTag), graphElem;
    while (!elem.isNull()) {
        v = new Vertex();
        v->load(elem);
        graphElem = elem.firstChildElement(graphTag);
        if(!graphElem.isNull()) {
            g = new Graph();
            g->load(graphElem);
            v->setGraph(g);
        }
        addVertex(v, elem.attribute("id"));
        elem = elem.nextSiblingElement(vertexTag);
    }

    // Parse edges
    Edge *e;
    elem = element.firstChildElement(edgeTag);
    while(!elem.isNull()) {
        e = new Edge();
        e->setOrigin(vertices_[verticesInsertionOrder_[elem.attribute("from")]]);
        e->setTarget(vertices_[verticesInsertionOrder_[elem.attribute("to")]]);
        e->load(elem);
        if(edgeids)
            e->setID(elem.attribute("id"));
        graphElem = elem.firstChildElement(graphTag);
        if(!graphElem.isNull()) {
            g = new Graph();
            g->load(graphElem);
            e->setGraph(g);
        }
        addEdge(e);
        // e may be deleted
        e = edges_.last();
        e->getOrigin()->addEdge(e, Vertex::EDGE_OUT);
        e->getTarget()->addEdge(e, Vertex::EDGE_IN);

        elem = elem.nextSiblingElement(edgeTag);
    }
}

QDomElement Graph::save(QDomDocument *document) {
    QDomElement graph = GraphElement::save(document);
    if(!getID().isEmpty())
        graph.setAttribute("id", getID());
    graph.setAttribute("edgemode", toName(type_));
    bool edgeids = (getEdgeCount() > 0) && !getEdge(0)->getID().isEmpty();
    graph.setAttribute("edgeids", Attribute::toString(QMetaType::Bool, edgeids));

    QDomElement element;
    for(Vertex *v : vertices_) {
        element = v->save(document);
        element.setAttribute("id", v->getID());
        if(v->getGraph())
            element.appendChild(v->getGraph()->save(document));
        graph.appendChild(element);
    }
    for(Edge *e : edges_) {
        element = e->save(document);
        if(edgeids)
            element.setAttribute("id", e->getID());
        element.setAttribute("from", e->getOrigin()->getID());
        element.setAttribute("to", e->getTarget()->getID());
        if(e->getGraph())
            element.appendChild(e->getGraph()->save(document));
        graph.appendChild(element);
    }
    return graph;
}

void Graph::fromGML(const QString &filename) {
    QString buffer = FileUtils::load(filename);
    QRegExp directed = QRegExp("directed (0|1)");
    QRegExp vertex_begin = QRegExp(GraphElement::toName(GraphElement::VERTEX) + " \\[");
    QRegExp edge_begin = QRegExp(GraphElement::toName(GraphElement::EDGE) + " \\[");
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
                    if((it+1)->contains('\"')) {
                        v->addAttribute(*it, QMetaType::QString, *(it+1));
                    } else {
                        if((it+1)->contains("."))
                            v->addAttribute(*it, QMetaType::Double, (it+1)->toDouble());
                        else
                            v->addAttribute(*it, QMetaType::Int, (it+1)->toInt());
                    }
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
                    if((it+1)->contains('\"')) {
                        e->addAttribute(*it, QMetaType::QString, *(it+1));
                    } else {
                        if((it+1)->contains("."))
                            e->addAttribute(*it, QMetaType::Double, (it+1)->toDouble());
                        else
                            e->addAttribute(*it, QMetaType::Int, (it+1)->toInt());
                    }
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

void Graph::fromXML() {
    QString graphTag = GraphElement::toName(GraphElement::GRAPH);
    QDomElement graph = document()->documentElement().firstChildElement(graphTag);
    load(graph);
}

void Graph::fromXMLMetadata(const QString &filename) {
    metadata_->load(filename);
    QString graphFile = metadata_->getGraphAttribute("graphfile").toString();
    if(!FileUtils::isAbsolute(graphFile))
        graphFile = FileUtils::slashed(FileUtils::path(filename), graphFile);
    load(graphFile);
}

void Graph::toGML(const QString &filename) {
    FileUtils::save(this, filename);
}

void Graph::toXML() {
    QDomElement gxl = document()->createElement("gxl");
    QDomElement graph = save(document());
    gxl.appendChild(graph);
    document()->appendChild(gxl);
}

void Graph::toXMLMetadata(const QString &filename) {
    metadata_->save(filename);
    QString graphFile = metadata_->getGraphAttribute("graphfile").toString();
    if(!FileUtils::isAbsolute(graphFile))
        graphFile = FileUtils::slashed(FileUtils::path(filename), graphFile);
    save(graphFile);
}

void Graph::print(Printer *p) {
    p->dump("graph [");
    p->indent();
    p->dump(QString("directed %1").arg(type_ == DIRECTED));
    // Vertices
    for(auto v : vertices_) {
        p->dump(GraphElement::toName(GraphElement::VERTEX) + " [");
        p->indent();
        p->dump(QString("id %1").arg(v->getIndex()));
        p->dump(QString("label \"%1\"").arg(v->getID()));
        for(auto key : v->getAttributes().keys()) {
            Attribute *att = v->getAttribute(key);
            QString pattern = att->isTextBased()? "%1 \"%2\"" : "%1 %2";
            p->dump(pattern.arg(key, att->toString()));
        }
        p->unindent();
        p->dump("]");
    }
    // Edges
    for(auto e : edges_) {
        p->dump(GraphElement::toName(GraphElement::EDGE) + " [");
        p->indent();
        p->dump(QString("source %1").arg(e->getOrigin()->getIndex()));
        p->dump(QString("target %1").arg(e->getTarget()->getIndex()));
        for(auto key : e->getAttributes().keys()) {
            Attribute *att = e->getAttribute(key);
            QString pattern = att->isTextBased()? "%1 \"%2\"" : "%1 %2";
            p->dump(pattern.arg(key, att->toString()));
        }
        p->unindent();
        p->dump("]");
    }
    p->unindent();
    p->dump("]");
}
