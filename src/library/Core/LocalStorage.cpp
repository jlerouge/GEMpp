#include "LocalStorage.h"

LocalStorage::LocalStorage(const QString &uniqueID) : Identified(uniqueID) {
    if(uniqueID.isEmpty())
        setID(createUniqueID());
}

LocalStorage::LocalStorage(const LocalStorage &other) : Identified(other) {}

LocalStorage::~LocalStorage() {}

QDir LocalStorage::getDir() {
    return QDir(getPath());
}

QString LocalStorage::getPath() {
    return FileUtils::slashed(getLocalDir(), getID());
}

bool LocalStorage::exists() {
    return getDir().exists();
}

bool LocalStorage::create() {
    return getLocalDir().mkpath(getID());
}

bool LocalStorage::remove() {
    return getDir().removeRecursively();
}

QString LocalStorage::createUniqueID() {
    return QUuid::createUuid().toString();
}

QDir LocalStorage::getLocalDir() {
    return QDir(getLocalPath());
}

QString LocalStorage::getLocalPath() {
    return QStandardPaths::standardLocations(QStandardPaths::DataLocation).first();
}
