#ifndef NETWORKUPDATER_H
#define NETWORKUPDATER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QHash>
#include <QLinkedList>
#include <QPair>

#include "transfertypedefs.h"
#include "networkinterface.h"
#include "networkstorage.h"
#include "networkgraph.h"

class NetworkUpdater : public QObject
{
    Q_OBJECT

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

public:
    explicit NetworkUpdater(quint64 interval, NetworkStorage* storage, QObject *parent = 0);
    SnapshotList snapshots;

signals:

private slots:
    void update();

public slots:

};

#endif // NETWORKUPDATER_H
