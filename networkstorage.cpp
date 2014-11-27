#include "networkstorage.h"

NetworkStorage::NetworkStorage(QObject *parent) :
    QObject(parent)
{
    savedData = QHash<QString, QMap<QDateTime, StoredData>>();

    auto rootFolder = getAppFolder();
    auto flags = QDir::Readable | QDir::NoDotAndDotDot | QDir::Dirs | QDir::NoSymLinks;
    QDirIterator yearIt(rootFolder, flags, QDirIterator::NoIteratorFlags);
    while (yearIt.hasNext()) {
        auto yearPath = yearIt.next();
        auto year = yearIt.fileName();
        qDebug() << yearPath;

        QDirIterator monthIt(yearPath, flags);
        while (monthIt.hasNext()) {
            auto monthPath = monthIt.next();
            auto month = monthIt.fileName();
            qDebug() << monthPath;

            QDirIterator dayIt(monthPath, flags);
            while (dayIt.hasNext()) {
                auto dayPath = dayIt.next();
                auto day = dayIt.fileName();
                qDebug() << dayPath;

                QDirIterator hourIt(dayPath, flags);
                while (hourIt.hasNext()) {
                    auto hourPath = hourIt.next();
                    auto hour = hourIt.fileName();
                    qDebug() << hourPath;

                    auto date = QDate(year.toInt(), month.toInt(), day.toInt());
                    auto time = QTime(hour.toInt(), 0, 0);
                    auto dateTime = QDateTime(date, time, Qt::UTC);
                    qDebug() << dateTime;

                    QDirIterator ifIt(hourPath, QDir::Readable | QDir::NoDotAndDotDot | QDir::Files | QDir::NoSymLinks);
                    while (ifIt.hasNext()) {
                        auto ifPath = ifIt.next();
                        auto ifFileName = ifIt.fileName();
                        auto ifName = ifFileName;
                        ifName.chop(5);
                        qDebug() << ifName;

                        if (savedData.find(ifName) == savedData.end())
                        {
                            savedData.insert(ifName, QMap<QDateTime, StoredData>());
                        }

                        QFile file(ifPath);
                        if (!file.open(QIODevice::ReadOnly))
                        {
                            throw QString("Couldn't open the file!");
                        }

                        auto contents = file.readAll();
                        auto doc = QJsonDocument(QJsonDocument::fromJson(contents));
                        auto obj = doc.object();

                        auto data = StoredData();
                        data.dlAmount = obj["rx"].toString().toULongLong();
                        data.ulAmount = obj["tx"].toString().toULongLong();

                        auto map = *savedData.find(ifName);
                        map.insert(dateTime, data);

                        savedData.insert(ifName, map);
                    }
                }
            }
        }
    }
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

    QJsonDocument doc = QJsonDocument();
    if (exists)
    {
        if (!file.open(QIODevice::ReadOnly))
        {
            throw QString("Couldn't open the file!");
        }

        auto contents = file.readAll();
        doc = QJsonDocument(QJsonDocument::fromJson(contents));
    }

    file.close();
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
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
        jsonObject = doc.object();

        if (jsonObject.find(trStr) != jsonObject.end())
        {
            oldValue = jsonObject[trStr].toString().toULongLong();
        }
    }

    if (savedData.find(interface) == savedData.end())
    {
        savedData.insert(interface, QMap<QDateTime, StoredData>());
    }

    auto map = *savedData.find(interface);
    auto data = map.value(time);
    if (type == NetworkTransferType::Download)
    {
        data.dlAmount = oldValue + amount;
    }
    else
    {
        data.ulAmount = oldValue + amount;
    }
    map.insert(time, data);
    savedData.insert(interface, map);

    jsonObject.insert(trStr, QVariant(oldValue + amount).toString());

    doc.setObject(jsonObject);
    file.write(doc.toJson());
}

QString NetworkStorage::getFolderForTime(QDateTime time)
{
    auto realDate = time.date();
    auto realTime = time.time();

    auto rootFolder = getAppFolder();
    auto fullPath =
            rootFolder + "/" +
            QVariant(realDate.year()).toString() + "/" +
            QVariant(realDate.month()).toString() + "/" +
            QVariant(realDate.day()).toString() + "/" +
            QVariant(realTime.hour()).toString();

    return fullPath;
}

QString NetworkStorage::getAppFolder()
{
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation);
}
