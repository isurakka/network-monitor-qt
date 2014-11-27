#ifndef NETWORKSTORAGE_H
#define NETWORKSTORAGE_H

#include <QObject>
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDirIterator>
#include <QHash>

#include "networkunit.h"

class NetworkStorage : public QObject
{
    Q_OBJECT


    class StoredData
    {
    public:
            quint64 dlAmount;
            quint64 ulAmount;
    };

private:
    static QString getFolderForTime(QDateTime time);
    static QString getAppFolder();

public:
    explicit NetworkStorage(QObject *parent = 0);
    void addData(QDateTime time, NetworkTransferType type, quint64 amount, QString interface);
    QHash<QString, QMap<QDateTime, StoredData>> savedData;

signals:

public slots:

};

#endif // NETWORKSTORAGE_H
