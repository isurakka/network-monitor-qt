#ifndef NETWORKSTORAGE_H
#define NETWORKSTORAGE_H

#include <QObject>
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "networkunit.h"

class NetworkStorage : public QObject
{
    Q_OBJECT

private:
    static QString getFolderForTime(QDateTime time);

public:
    explicit NetworkStorage(QObject *parent = 0);
    void addData(QDateTime time, NetworkTransferType type, quint64 amount, QString interface);

signals:

public slots:

};

#endif // NETWORKSTORAGE_H
