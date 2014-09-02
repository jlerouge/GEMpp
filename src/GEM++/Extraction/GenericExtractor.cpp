#include "GenericExtractor.h"

GenericExtractor::GenericExtractor() {}

GenericExtractor::GenericExtractor(const QVariant &input, const QVariant &output, const QVariant &metadata, ExtractionConfiguration *excfg) :
    input_(input), output_(output), metadata_(metadata), excfg_(excfg) {}

GenericExtractor::~GenericExtractor() {}

void GenericExtractor::setInput(const QVariant &input) {
    input_ = input;
}

QVariant GenericExtractor::getInput() const {
    return input_;
}

void GenericExtractor::setOutput(const QVariant &output) {
    output_ = output;
}

QVariant GenericExtractor::getOutput() const {
    return output_;
}

void GenericExtractor::setMetadata(const QVariant &metadata) {
    metadata_ = metadata;
}

QVariant GenericExtractor::getMetadata() const {
    return metadata_;
}

void GenericExtractor::setConfiguration(ExtractionConfiguration *excfg) {
    excfg_ = excfg;
}

ExtractionConfiguration *GenericExtractor::getConfiguration() const {
    return excfg_;
}

void GenericExtractor::extract() {
    performExtraction();
}
