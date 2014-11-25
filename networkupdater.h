#ifndef NETWORKUPDATER_H
#define NETWORKUPDATER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QHash>
#include <QLinkedList>
#include <QPair>

#include "networkunit.h"
#include "networkinterface.h"
#include "networkstorage.h"

class NetworkUpdater : public QObject
{
    Q_OBJECT

    typedef QHash<NetworkTransferType, quint64> TransferTypeData;
    typedef QHash<QString, TransferTypeData> InterfaceData;

    typedef QPair<QDateTime, InterfaceData> DataSnapshot;
    typedef QLinkedList<DataSnapshot> SnapshotList;

private:
    QTimer* timer;
    quint64 interval;
    NetworkStorage* storage;
    QDateTime lastUpdate;
    bool firstUpdate;
    InterfaceData currentData;
    InterfaceData currentRawData;
    InterfaceData lastRawData;
    void emptyCurrentData();
    InterfaceData getCurrentRawData();
    void addDifferenceToCurrentData();
    int snapshotLimit;
    SnapshotList snapshots;

public:
    explicit NetworkUpdater(quint64 interval, NetworkStorage* storage, QObject *parent = 0);

signals:

private slots:
    void update();

public slots:

};

#endif // NETWORKUPDATER_H
