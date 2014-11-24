#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <QObject>
#include <QDirIterator>
#include <QDebug>

#include <networkunit.h>

class NetworkInterface
{
private:
    QString name;

public:
    NetworkInterface(QString name);
    static QStringList* getAllInterfaceNames();
    quint64 getCurrentAmount(NetworkTransferType type);
};

#endif // NETWORKINTERFACE_H
