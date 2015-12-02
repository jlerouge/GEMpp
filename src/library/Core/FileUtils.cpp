#include "FileUtils.h"

FileUtils::FileUtils() {}

FileUtils::~FileUtils() {}

QString FileUtils::load(const QString &filename) {
    exists(filename);
    QFile f(filename);
    open(f, QFile::ReadOnly);
    QString res = f.readAll();
    close(f);
    return res;
}

void FileUtils::save(IPrintable *ip, const QString &filename, bool append) {
    Printer p;
    ip->print(&p);
    save(p.getContent(), filename, append);
}

void FileUtils::save(const QString &s, const QString &filename, bool append) {
    QFile f(filename);
    open(f, QFile::ReadWrite | (append? QFile::Append : QFile::Truncate));
    QTextStream stream (&f);
    stream << s;
    close(f);
}

bool FileUtils::remove(const QString &filename) {
    QFile f(filename);
    return f.remove();
}

void FileUtils::open(QFile &file, QFile::OpenMode mode) {
    if(!file.open(mode | QFile::Text))
        Exception(QString("The file \"%1\" cannot be opened : %2").arg(file.fileName(), file.errorString()));
}

void FileUtils::close(QFile &file) {
    file.close();
}

QString FileUtils::getExtension(const QString &filename) {
    return QFileInfo(filename).suffix();
}

void FileUtils::checkExtension(const QString &filename, const QString &extension) {
    if(QFileInfo(filename).suffix().compare(extension, Qt::CaseInsensitive) != 0)
        Exception(QString("The file \"%1\" is not a *.%2 file.").arg(filename,extension));
}

QString FileUtils::changeExtension(const QString &filename, const QString &extension) {
    return removeExtension(filename) + "." + extension;
}

QString FileUtils::removeExtension(const QString &filename) {
    QFileInfo fi(filename);
    return slashed(fi.path(), fi.baseName());
}

bool FileUtils::exists(const QString &filename) {
    return QFileInfo(filename).exists();
}

bool FileUtils::exists(const QDir &path) {
    return path.exists();
}

void FileUtils::checkExists(const QString &filename) {
    if(!exists(filename))
        Exception(QString("The file \"%1\" does not exist.").arg(filename));
}

void FileUtils::checkExists(const QDir &path) {
    if(!exists(path))
        Exception(QString("The directory \"%1\" does not exist.").arg(path.path()));
}

bool FileUtils::isValid(const QString &filename) {
    return !(filename.isEmpty());
}

void FileUtils::checkValid(const QString &filename) {
    if(!isValid(filename))
        Exception("The given filename is empty.");
}

QDir FileUtils::slashed(const QDir &parent, const QDir &path) {
    return QDir(slashed(parent.path(), path.path()));
}

QString FileUtils::slashed(const QDir &parent, const QString &path) {
    return slashed(parent.path(), path);
}

QString FileUtils::slashed(const QString &parent, const QString &path) {
    if(isAbsolute(path) || parent.compare(".") == 0)
        return path;
    return parent + "/" + path;
}

QString FileUtils::path(const QString &filepath) {
    return QFileInfo(filepath).path();
}

QDir FileUtils::dir(const QString &filepath) {
    return QFileInfo(filepath).dir();
}

QString FileUtils::filename(const QString &filepath) {
    return QFileInfo(filepath).fileName();
}

bool FileUtils::isAbsolute(const QString &path) {
    return QFileInfo(path).isAbsolute();
}

bool FileUtils::containsImages(const QDir &dir) {
    return !(dir.entryList(QString(IMG_FORMATS).split(" "), QDir::Files).isEmpty());
}

bool FileUtils::createPath(const QString &parent, const QString &path) {
    return QDir(parent).mkpath(path);
}

QString FileUtils::checkCreatedPathExists(const QString &parent, const QString &path) {
    if(!createPath(parent, path))
        Exception(QString("Could not create path \"%1\"").arg(slashed(parent, path)));
    return slashed(parent, path);
}
