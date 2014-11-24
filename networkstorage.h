#ifndef NETWORKSTORAGE_H
#define NETWORKSTORAGE_H

#include <QObject>
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>
#include <QDebug>

#include "networkunit.h"

class NetworkStorage : public QObject
{
    Q_OBJECT

private:
    void createFolders(QDateTime time);
    static QString getFolderForTime(QDateTime time);

public:
    explicit NetworkStorage(QObject *parent = 0);
    void addData(QDateTime time, NetworkTransferType type, quint64 amount);

signals:

public slots:

};

#endif // NETWORKSTORAGE_H
