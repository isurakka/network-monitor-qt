#include "networkstorage.h"

NetworkStorage::NetworkStorage(QObject *parent) :
    QObject(parent)
{
}

void NetworkStorage::createFolders(QDateTime time)
{

    //auto full
    //        qDebug() << rootFolder;
}

QString NetworkStorage::getFolderForTime(QDateTime time)
{
    auto realDate = time.date();
    auto realTime = time.time();

    auto rootFolder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    auto fullPath =
            rootFolder + "/" +
            QVariant(realDate.year()).toString() + "/" +
            QVariant(realDate.month()).toString() + "/" +
            QVariant(realDate.day()).toString() + "/" +
            QVariant(realTime.hour()).toString();

    //QDir::mkpath(fullPath);

    return fullPath;
}
