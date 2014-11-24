#include "overviewupdater.h"

OverviewUpdater::OverviewUpdater(QObject* container, ApplicationSettings* settings, QObject *parent, int interval) :
    QObject(parent)
{
    this->container = container;
    this->settings = settings;

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(interval);
}

void OverviewUpdater::update()
{
    qDebug() << "Overview update";

    auto interface = settings->getCurrentInterface();
    auto unit = settings->getCurrentUnit();
    auto realBytes = (qreal)unit.getBytes();

    auto unitPost = " " + unit.getDisplayName() + "/s";

    auto currentDownload = interface.getCurrentAmount(NetworkTransferType::Download);
    auto currentUpload = interface.getCurrentAmount(NetworkTransferType::Upload);

    auto diffDownload = currentDownload - lastDownload;
    auto diffUpload = currentUpload - lastUpload;

    auto finalDownload = QString::number(((qreal)diffDownload) / realBytes, 'f', 2);
    auto finalUpload = QString::number(((qreal)diffUpload) / realBytes, 'f', 2);

    auto downloadElement = container->findChild<QObject*>("currentDownloadValue");
    downloadElement->setProperty("text", QVariant(finalDownload).toString() + unitPost);

    auto uploadElement = container->findChild<QObject*>("currentUploadValue");
    uploadElement->setProperty("text", QVariant(finalUpload).toString() + unitPost);

    lastDownload = currentDownload;
    lastUpload = currentUpload;
}
