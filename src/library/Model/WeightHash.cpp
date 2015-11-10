#include "WeightHash.h"

const char* WeightHash::modeName[WeightHash::COUNT] = {
    "Add",
    "Multiply"
};

WeightHash::Mode WeightHash::fromName(QString name) {
    for(Mode mode = (Mode)0; mode < COUNT; mode = (Mode)((int)mode + 1))
        if(QString(modeName[mode]).startsWith(name, Qt::CaseInsensitive))
            return mode;
    Exception(QString("Mode '%1' not recognized, please use a(dd) or m(ultiply).").arg(name));
    return COUNT;
}

QString WeightHash::toName(Mode mode) {
    return modeName[mode];
}

WeightHash::WeightHash(Mode mode, uint root) : mode_(mode), root_(root) {}

WeightHash::~WeightHash() {
    for(auto w : values())
        delete w;
}

WeightHash::Mode WeightHash::getMode() const {
    return mode_;
}

void WeightHash::setMode(Mode mode) {
    mode_ = mode;
}

uint WeightHash::getRoot() const {
    return root_;
}

void WeightHash::setRoot(uint root) {
    root_ = root;
}
