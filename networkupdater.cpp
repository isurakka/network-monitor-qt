#include "networkupdater.h"

NetworkUpdater::NetworkUpdater(quint64 interval, QObject *parent) :
    QObject(parent)
{
    this->interval = interval;

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(interval);
}

void NetworkUpdater::update()
{

}
