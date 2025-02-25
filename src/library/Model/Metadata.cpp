#include "Metadata.h"

Metadata::Metadata() {
    graphAttributes_ = QMap<QString, QString>();
    verticesAttributes_ = QMap<int, QMap<QString, QString> >();
    edgesAttributes_ = QMap<int, QMap<QString, QString> >();
    attributes[GraphElement::VERTEX] = &verticesAttributes_;
    attributes[GraphElement::EDGE] = &edgesAttributes_;
}

Metadata::Metadata(const QString &filename) : Metadata() {
    if(!filename.endsWith(".xml", Qt::CaseInsensitive))
        Exception(QString("%1 is not a *.xml file.").arg(filename));
    load(filename);
}

Metadata::~Metadata() {
    clean();
}

QVariant Metadata::getGraphAttribute(QString name) const {
    if(!graphAttributes_.contains(name))
        Exception(QString("Graph metadata does not contain %1 attribute").arg(name));
    return QVariant(graphAttributes_[name]);
}

void Metadata::setGraphAttribute(QString name, QVariant value) {
    graphAttributes_.insert(name, value.toString());
}

const QMap<QString, QString> &Metadata::getGraphAttributes() const {
    return graphAttributes_;
}

QVariant Metadata::getAttribute(GraphElement::Type type, uint index, QString name) const {
    if(!attributes[type]->contains(index))
        Exception(QString("%1 at index %2 does not have metadata").arg(GraphElement::toName(type)).arg(index));
    if(!attributes[type]->value(index).contains(name))
        Exception(QString("Metadata of %1 at index %2 does not contain %3 attribute").arg(GraphElement::toName(type)).arg(index).arg(name));
    return QVariant(attributes[type]->value(index).value(name));
}

void Metadata::setAttribute(GraphElement::Type type, uint index, QString name, QVariant value) {
    if(!attributes[type]->contains(index))
        attributes[type]->insert(index, QMap<QString, QString>());
    QMap<QString, QString> map = attributes[type]->value(index);
    map.insert(name, value.toString());
    attributes[type]->insert(index, map);
}

const QMap<QString, QString> Metadata::getAttributes(GraphElement::Type type, uint index) const {
    if(!attributes[type]->contains(index))
        Exception(QString("%1 at index %2 does not have metadata").arg(GraphElement::toName(type)).arg(index));
    return attributes[type]->value(index);
}

void Metadata::fromXML() {
    verticesAttributes_.clear();
    edgesAttributes_.clear();

    QDomElement graph, vertex, edge;
    graph = document()->documentElement();
    for(int i=0; i < graph.attributes().length(); ++i)
        graphAttributes_.insert(graph.attributes().item(i).nodeName(), graph.attributes().item(i).nodeValue());
    vertex = graph.firstChildElement("Node");
    uint index = 0;
    while(!vertex.isNull()) {
        verticesAttributes_.insert(index, QMap<QString,QString>());
        for(int i=0; i < vertex.attributes().length(); ++i)
            verticesAttributes_[index].insert(vertex.attributes().item(i).nodeName(), vertex.attributes().item(i).nodeValue());
        vertex = vertex.nextSiblingElement("Node");
        ++index;
    }
    edge = graph.firstChildElement("Edge");
    index = 0;
    while(!edge.isNull()) {
        edgesAttributes_.insert(index, QMap<QString,QString>());
        for(int i=0; i < edge.attributes().length(); ++i)
            edgesAttributes_[index].insert(edge.attributes().item(i).nodeName(), edge.attributes().item(i).nodeValue());
        edge = edge.nextSiblingElement("Edge");
        ++index;
    }
}

void Metadata::toXML() {
    QDomElement graph, vertex, edge;
    graph = document()->createElement("Graph");
    for(auto key : graphAttributes_.keys())
        graph.setAttribute(key, graphAttributes_[key]);
    for(auto index : verticesAttributes_.keys()) {
        vertex = document()->createElement("Node");
        for(auto key : verticesAttributes_[index].keys())
            vertex.setAttribute(key, verticesAttributes_[index][key]);
        graph.appendChild(vertex);
    }
    for(auto index : edgesAttributes_.keys()) {
        edge = document()->createElement("Edge");
        for(auto key : edgesAttributes_[index].keys())
            edge.setAttribute(key, edgesAttributes_[index][key]);
        graph.appendChild(edge);
    }
    document()->appendChild(graph);
}
