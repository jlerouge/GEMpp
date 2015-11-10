#include "FileStream.h"

FileStream::FileStream() {}

FileStream::~FileStream() {}

QString FileStream::loadFile(const QString &filename) {
    QString res;
    QFile f(filename);

    if(!f.exists())
        Exception(QString("%1 does not exist.").arg(filename));

    if(f.open(QIODevice::ReadOnly)) {
        res = f.readAll();
        if(res.length() <= 1)
            Exception(QString("%1 is empty.").arg(filename));
        f.close();
    } else
        Exception(QString("%1 cannot be opened.").arg(filename));
    return res;
}

void FileStream::saveFile(IPrintable *ip, const QString &filename) {
    Printer p;
    ip->print(&p);
    saveFile(p.getContent(), filename);
}

void FileStream::saveFile(const QString &s, const QString &filename) {
    QFile f(filename);
    if(f.open(QIODevice::WriteOnly)) {
        QTextStream stream (&f);
        stream << s;
        f.close();
    } else
        Exception(QString("%1 cannot be opened.").arg(filename));
}

bool FileStream::removeFile(const QString &filename) {
    QFile f(filename);
    return f.remove();
}
