#include "LocalStorage.h"

PIVAJ::LocalStorage::LocalStorage(const QString &uniqueID) : Identified(uniqueID) {
    if(uniqueID.isEmpty())
        setID(createUniqueID());
}

PIVAJ::LocalStorage::LocalStorage(const LocalStorage &other) : Identified(other) {}

PIVAJ::LocalStorage::~LocalStorage() {}

QDir PIVAJ::LocalStorage::getDir() {
    return QDir(getPath());
}

QString PIVAJ::LocalStorage::getPath() {
    return FileUtils::slashed(getLocalDir(), getID());
}

bool PIVAJ::LocalStorage::exists() {
    return getDir().exists();
}

bool PIVAJ::LocalStorage::create() {
    return getLocalDir().mkpath(getID());
}

bool PIVAJ::LocalStorage::remove() {
    return getDir().removeRecursively();
}

QString PIVAJ::LocalStorage::createUniqueID() {
    return QUuid::createUuid().toString();
}

QDir PIVAJ::LocalStorage::getLocalDir() {
    return QDir(getLocalPath());
}

QString PIVAJ::LocalStorage::getLocalPath() {
    return QStandardPaths::standardLocations(QStandardPaths::DataLocation).first();
}
