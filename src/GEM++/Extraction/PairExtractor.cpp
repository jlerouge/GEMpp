#include "PairExtractor.h"

PairExtractor::PairExtractor() {}

PairExtractor::PairExtractor(const QPair<QString, QString> &inputs, const QPair<QString, QString> &outputs, const QPair<QString, QString> &metadata, ExtractionConfiguration *excfg) {
    setInput(inputs);
    setOutput(outputs);
    setMetadata(metadata);
    setConfiguration(excfg);
}

PairExtractor::~PairExtractor() {}

void PairExtractor::setInput(const QPair<QString, QString> &filenames) {
    input_ = QVariant(toList(filenames));
}

QPair<QString, QString> PairExtractor::getInput() const {
    return toPair(input_.toStringList());
}

void PairExtractor::setOutput(const QPair<QString, QString> &filenames) {
    output_ = QVariant(toList(filenames));
}

QPair<QString, QString> PairExtractor::getOutput() const {
    return toPair(output_.toStringList());
}

void PairExtractor::setMetadata(const QPair<QString, QString> &filenames) {
    metadata_ = QVariant(toList(filenames));
}

QPair<QString, QString> PairExtractor::getMetadata() const {
    return toPair(metadata_.toStringList());
}

QStringList PairExtractor::toList(const QPair<QString, QString> &pair) {
    QStringList list;
    list.append(pair.first);
    list.append(pair.second);
    return list;
}

QPair<QString, QString> PairExtractor::toPair(const QStringList &list) {
    if(list.size() != 2)
        GEM_exception(QString("QStringList must have 2 elements to be casted to QPair<QString, QString> (instance has %1 elements)").arg(list.size()));
    return qMakePair(list[0], list[1]);
}
