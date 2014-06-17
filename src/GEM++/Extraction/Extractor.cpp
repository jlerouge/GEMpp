#include "Extractor.h"

Extractor::Extractor() : input_(""), output_(""), metadata_(""), excfg_(0) {}

Extractor::Extractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg) : Extractor() {
    setInputFile(input);
    setOutputFile(output);
    setMetadataFile(metadata);
    configure(excfg);
}

Extractor::~Extractor() {}

void Extractor::setInputFile(const QString &filename) {
    input_ = filename;
}

QString Extractor::getInputFile() {
    return input_;
}

void Extractor::setOutputFile(const QString &filename) {
    output_ = filename;
}

QString Extractor::getOutputFile() {
    return output_;
}

void Extractor::setMetadataFile(const QString &filename) {
    metadata_ = filename;
}

QString Extractor::getMetadataFile() {
    return metadata_;
}

void Extractor::configure(ExtractionConfiguration *excfg) {
    excfg_ = excfg;
}

ExtractionConfiguration *Extractor::getConfig() {
    return excfg_;
}

void Extractor::extract() {
    performExtraction();
}
