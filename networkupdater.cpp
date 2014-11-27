#include "networkupdater.h"

NetworkUpdater::NetworkUpdater(quint64 interval, ApplicationSettings* settings, NetworkStorage* storage, QObject *parent) :
    QObject(parent),
    interval(interval),
    settings(settings),
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

        // Update current speed
        auto interface = settings->getCurrentInterface().getName();
        auto unit = settings->getCurrentUnit();
        auto realBytes = (qreal)unit.getBytes();

        auto unitPost = " " + unit.getDisplayName() + "/s";

        auto diffDownload = currentData.value(interface).value(NetworkTransferType::Download);
        auto diffUpload = currentData.value(interface).value(NetworkTransferType::Upload);

        auto finalDownload = QString::number(((qreal)diffDownload) / realBytes, 'f', 2);
        auto finalUpload = QString::number(((qreal)diffUpload) / realBytes, 'f', 2);

        auto downloadElement = parent()->findChild<QObject*>("currentDownloadValue");
        downloadElement->setProperty("text", QVariant(finalDownload).toString() + unitPost);

        auto uploadElement = parent()->findChild<QObject*>("currentUploadValue");
        uploadElement->setProperty("text", QVariant(finalUpload).toString() + unitPost);

        // Update graphs
        for (auto& graph : parent()->findChildren<NetworkGraph*>())
        {
            graph->update();

            auto finalMax = QString::number(((qreal)graph->graphMax) / realBytes, 'f', 2);

            graph->parent()->findChild<QObject*>("maxLabel")->setProperty("text", "Max " + QVariant(finalMax).toString() + unitPost);
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
