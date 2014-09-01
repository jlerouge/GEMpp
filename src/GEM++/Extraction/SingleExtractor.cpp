#include "SingleExtractor.h"

SingleExtractor::SingleExtractor() {}

SingleExtractor::SingleExtractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg) {
    setInput(input);
    setOutput(output);
    setMetadata(metadata);
    setConfiguration(excfg);
}

SingleExtractor::~SingleExtractor() {}

QString SingleExtractor::getInput() {
    return input_.toString();
}

QString SingleExtractor::getOutput() {
    return output_.toString();
}

QString SingleExtractor::getMetadata() {
    return metadata_.toString();
}
