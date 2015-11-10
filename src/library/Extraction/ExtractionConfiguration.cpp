#include "ExtractionConfiguration.h"

ExtractionConfiguration::ExtractionConfiguration() {
    reset();
}

ExtractionConfiguration::~ExtractionConfiguration() {}

void ExtractionConfiguration::reset() {
    verbose = false;
    pruningSize = 0;
    tolerance = 0;
    zernikeOrder = 0;
}

void ExtractionConfiguration::print(Printer *p) {
    p->dump("ExtractionConfiguration {");
    p->indent();
    p->dump(QString("verbose : %1").arg(verbose));

    p->dump(QString("pruningSize : %1").arg(pruningSize));
    p->dump(QString("tolerance : %1").arg(tolerance));
    p->unindent();
    p->dump("}");
}

