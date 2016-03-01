#include "Printer.h"

Printer::Printer(int indentWidth) : content_(""), indentWidth_(indentWidth), indentLevel_(0) {}

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

QString Printer::capitalize(QString s) {
    QStringList sl = s.split(" ");
    QStringList slc;
    for(QString w : sl)
        slc.append(capitalizeWord(w));
    return slc.join(" ");
}

QString Printer::capitalizeWord(QString w) {
    return w.left(1).toUpper() + w.mid(1).toLower();
}
