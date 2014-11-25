#include "networkstorage.h"

NetworkStorage::NetworkStorage(QObject *parent) :
    QObject(parent)
{
}

void NetworkStorage::addData(QDateTime time, NetworkTransferType type, quint64 amount, QString interface)
{
    auto folder = QDir(getFolderForTime(time));
    if (!folder.exists())
    {
        folder.mkpath(".");
    }

    QFile file(folder.absolutePath() + "/" + interface + ".json");

    bool exists = file.exists();

    if (!file.open(QIODevice::ReadWrite))
    {
        throw QString("Couldn't open the file!");
    }

    auto trStr = NetworkUnit::getStrForNetworkTransferType(type);

    QJsonObject jsonObject;
    quint64 oldValue;
    if (!exists)
    {
        jsonObject = QJsonObject();
    }
    else
    {
        QJsonDocument doc(QJsonDocument::fromBinaryData(file.readAll()));
        jsonObject = doc.object();

        if (jsonObject.find(trStr) != jsonObject.end())
        {
            oldValue = jsonObject[trStr].toString().toULongLong();
        }
    }

    jsonObject[trStr] = QVariant(oldValue + amount).toString();

    QJsonDocument doc(jsonObject);
    file.write(doc.toJson());
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

    return fullPath;
}
