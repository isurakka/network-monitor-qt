#ifndef NETWORKUPDATER_H
#define NETWORKUPDATER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QHash>
#include <QLinkedList>
#include <QPair>
#include <QQmlApplicationEngine>
#include <QQmlContext>

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
    ApplicationSettings* settings;
    QDateTime lastUpdate;
    bool firstUpdate;
    InterfaceData currentData;
    InterfaceData currentRawData;
    InterfaceData lastRawData;
    void emptyCurrentData();
    InterfaceData getCurrentRawData();
    void addDifferenceToCurrentData();
    int snapshotLimit;
    void refreshUI();
    QQmlApplicationEngine* engine;

public:
    explicit NetworkUpdater(quint64 interval, QQmlApplicationEngine* engine, ApplicationSettings* settings, NetworkStorage* storage, QObject *parent = 0);
    SnapshotList snapshots;

signals:

private slots:
    void update();
    void interfaceSelectionChanged(int index);
    void unitSelectionChanged(int index);

public slots:

};

#endif // NETWORKUPDATER_H
