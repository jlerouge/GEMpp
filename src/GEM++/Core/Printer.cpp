#include "Printer.h"

Printer::Printer(int indentWidth) : content_(""), indentLevel_(0), indentWidth_(indentWidth) {}

Printer::~Printer() {}

QString Printer::getContent() {
    return content_;
}

void Printer::setContent(const QString &content) {
    content_ = content;
}

int Printer::getIndentWidth() {
    return indentWidth_;
}

void Printer::setIndentWidth(int indentWidth) {
    indentWidth_ = indentWidth;
}

void Printer::dump(QString s) {
    for(int i=0; i<indentLevel_*indentWidth_; ++i) {
        content_ += " ";
    }
    content_ += s;
    newLine();
}

void Printer::show() {
    qcout << content_;
}

void Printer::indent() {
    ++indentLevel_;
}

void Printer::unindent() {
    --indentLevel_;
}

void Printer::newLine() {
    content_ += "\n";
}

void Printer::reset() {
    content_.clear();
}
