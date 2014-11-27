#include "networkupdater.h"

NetworkUpdater::NetworkUpdater(quint64 interval, NetworkStorage* storage, QObject *parent) :
    QObject(parent),
    interval(interval),
    storage(storage),
    firstUpdate(true),
    snapshotLimit(1000)
{
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(interval);
}

void NetworkUpdater::update()
{
    auto dateTime = QDateTime::currentDateTimeUtc();

    if (firstUpdate)
    {
        emptyCurrentData();
    }

    if (!firstUpdate && dateTime != lastUpdate)
    {
        InterfaceData::iterator i;
        for (i = currentData.begin(); i != currentData.end(); ++i)
        {
            TransferTypeData::iterator j;
            for (j = i.value().begin(); j != i.value().end(); ++j)
            {
                storage->addData(lastUpdate, j.key(), j.value(), i.key());
            }
        }
        snapshots.push_front(DataSnapshot(dateTime, currentData));

        for (auto& graph : parent()->findChildren<NetworkGraph*>())
        {
            //graph->repaint();
            graph->update();
        }

        emptyCurrentData();
    }

    currentRawData = getCurrentRawData();

    if (!firstUpdate)
    {
        addDifferenceToCurrentData();
    }

    lastRawData = currentRawData;

    firstUpdate = false;
    lastUpdate = dateTime;
}

void NetworkUpdater::emptyCurrentData()
{
    currentData = InterfaceData();

    auto interfaceNames = NetworkInterface::getAllInterfaceNames()->toVector();
    for (auto name : interfaceNames)
    {
        auto transferData = TransferTypeData();

        // TODO: Doesn't scale with enum
        transferData.insert(NetworkTransferType::Download, quint64(0));
        transferData.insert(NetworkTransferType::Upload, quint64(0));

        currentData.insert(name, transferData);
    }
}

InterfaceData NetworkUpdater::getCurrentRawData()
{
    auto data = InterfaceData();

    auto interfaceNames = NetworkInterface::getAllInterfaceNames()->toVector();
    for (auto name : interfaceNames)
    {
        auto interface = NetworkInterface(name);

        auto transferData = TransferTypeData();
        transferData.insert(NetworkTransferType::Download, interface.getCurrentAmount(NetworkTransferType::Download));
        transferData.insert(NetworkTransferType::Upload, interface.getCurrentAmount(NetworkTransferType::Upload));

        data.insert(name, transferData);
    }

    return data;
}

void NetworkUpdater::addDifferenceToCurrentData()
{
    InterfaceData::iterator i;
    for (i = currentData.begin(); i != currentData.end(); ++i)
    {
        TransferTypeData::iterator j;
        for (j = i.value().begin(); j != i.value().end(); ++j)
        {
            currentData[i.key()][j.key()] += currentRawData[i.key()][j.key()] - lastRawData[i.key()][j.key()];
        }
    }
}
