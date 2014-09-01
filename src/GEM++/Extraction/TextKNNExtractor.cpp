#include "TextKNNExtractor.h"

TextKNearestNeighborGraphExtractor::TextKNearestNeighborGraphExtractor() : PairExtractor() {
    query_ = 0;
    target_ = 0;
}

TextKNearestNeighborGraphExtractor::TextKNearestNeighborGraphExtractor(const QPair<QString, QString> &inputs, const QPair<QString, QString> &outputs,
                                                                       const QPair<QString, QString> &metadata, ExtractionConfiguration *excfg) :
    PairExtractor(inputs, outputs, metadata, excfg) {
    query_ = 0;
    target_ = 0;
}

TextKNearestNeighborGraphExtractor::~TextKNearestNeighborGraphExtractor() {
    delete query_;
    delete target_;
}

Graph* TextKNearestNeighborGraphExtractor::getQueryGraph() {
    return query_;
}

Graph* TextKNearestNeighborGraphExtractor::getTargetGraph() {
    return target_;
}

void TextKNearestNeighborGraphExtractor::performExtraction() {
    query_ = new Graph(Graph::UNDIRECTED);
    target_ = new Graph(Graph::UNDIRECTED);


    query_->save(getOutput().first);
    QDir dir = QFileInfo(getMetadata().first).absoluteDir();
    query_->getMetadata()->setGraphAttribute("graphfile", dir.relativeFilePath(QFileInfo(getOutput().first).absoluteFilePath()));
    query_->getMetadata()->save(getMetadata().first);

    target_->save(getOutput().second);
    dir = QFileInfo(getMetadata().second).absoluteDir();
    target_->getMetadata()->setGraphAttribute("graphfile", dir.relativeFilePath(QFileInfo(getOutput().second).absoluteFilePath()));
    target_->getMetadata()->save(getMetadata().second);
}
