#include "networkupdater.h"

NetworkUpdater::NetworkUpdater(quint64 interval, QQmlApplicationEngine* engine, ApplicationSettings* settings, NetworkStorage* storage, QObject *parent) :
    QObject(parent),
    interval(interval),
    engine(engine),
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
                storage->addData(dateTime, j.key(), j.value(), i.key());
            }
        }
        snapshots.push_front(DataSnapshot(dateTime, currentData));

        auto old = engine->rootContext()->contextProperty("hourlyModel");
        engine->rootContext()->setContextProperty("hourlyModel", 0);
        engine->rootContext()->setContextProperty("hourlyModel", old);

        if (!firstUpdate)
        {
            auto quota = checkQuota();
            if (quota != lastQuota)
            {
                auto quotaStatus = parent()->findChild<QQuickItem*>("quotaStatus");
                QString text;
                if (quota)
                {
                    text = "Status: Quota exceeded!";
                }
                else
                {
                    text = "Status: Ok";
                }
                quotaStatus->setProperty("text", text);
            }
            if (quota != lastQuota && quota)
            {
                qDebug() << "Quota exceeded!";

                QMessageBox::critical(0, "Quota", "Quota exceeded!", QMessageBox::Ok);
            }
            lastQuota = quota;
        }

        refreshUI();

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

void NetworkUpdater::refreshUI()
{
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
}

void NetworkUpdater::interfaceSelectionChanged(int index)
{
    qDebug() << "Interface selection changed";
    auto old = engine->rootContext()->contextProperty("hourlyModel");
    engine->rootContext()->setContextProperty("hourlyModel", 0);
    engine->rootContext()->setContextProperty("hourlyModel", old);
    refreshUI();
}

void NetworkUpdater::unitSelectionChanged(int index)
{
    qDebug() << "Unit selection changed";
    auto old = engine->rootContext()->contextProperty("hourlyModel");
    engine->rootContext()->setContextProperty("hourlyModel", 0);
    engine->rootContext()->setContextProperty("hourlyModel", old);
    refreshUI();
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
            currentData[i.key()][j.key()] = currentData[i.key()][j.key()] + (currentRawData[i.key()][j.key()] - lastRawData[i.key()][j.key()]);
        }
    }
}

bool NetworkUpdater::checkQuota()
{
    QSettings qS;
    auto enabled = qS.value("quotaEnabled").toBool();
    if (!enabled)
    {
        return false;
    }

    QDateTime min;
    QDateTime max = QDateTime::currentDateTimeUtc();

    auto type = qS.value("quotaType").toInt();
    if (type == 0)
    {
        min = max.addDays(-1);
    }
    else if (type == 1)
    {
        min = QDateTime(max.date(), QTime(), Qt::UTC);
    }
    else if (type == 2)
    {
        min = QDateTime(QDate(max.date().year(), max.date().month(), 1), QTime(), Qt::UTC);
    }

    auto unit = settings->getUnitForIndex(qS.value("quotaUnit").toInt());
    auto quotaAmount = qS.value("quotaAmount").toULongLong();

    for (auto it = storage->savedData.begin(); it != storage->savedData.end(); ++it)
    {
        auto currentAmount = quint64(0);

        auto value = (*it);
        QMap<QDateTime, NetworkStorage::StoredData>::iterator it2;
        for (it2 = value.begin(); it2 != value.end(); ++it2)
        {
            auto pair = it2;
            if (pair.key() >= min && pair.key() <= max)
            {
                currentAmount += pair.value().dlAmount;
                currentAmount += pair.value().ulAmount;
            }
        }

        currentAmount /= unit.getBytes();

        if (currentAmount >= quotaAmount)
        {
            // Quota exceeded
            return true;
        }
    }

    return false;
}
