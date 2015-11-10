#include "IXmlSerializable.h"

IXmlSerializable::IXmlSerializable() : doc_(0), filename_() {}

IXmlSerializable::~IXmlSerializable() {
    IXmlSerializable::clean();
}

QString IXmlSerializable::getFilename() const {
    return filename_;
}

void IXmlSerializable::setFilename(const QString &filename) {
    filename_ = filename;
}

void IXmlSerializable::load(const QString &filename) {
    if(!filename.isEmpty())
        filename_ = filename;
    FileUtils::checkExists(filename_);
    QFile file(filename_);
    FileUtils::open(file, QFile::ReadOnly);
    if(!doc_)
        doc_ = new QDomDocument();
    doc_->setContent(&file, true);
    fromXML();
    FileUtils::close(file);
    IXmlSerializable::clean();
}

void IXmlSerializable::save(const QString &filename) {
    if(!filename.isEmpty())
        filename_ = filename;
    FileUtils::checkValid(filename_);
    QString content = "<?xml version=\"1.0\"?>\n";
    if(!doc_)
        doc_ = new QDomDocument();
    toXML();
    content.append(doc_->toString(4));
    FileUtils::save(content, filename_);
    IXmlSerializable::clean();
}

void IXmlSerializable::clean() {
    if(doc_)
        delete doc_;
    doc_ = 0;
}

QDomDocument *IXmlSerializable::document() const {
    return doc_;
}
