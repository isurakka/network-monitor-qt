#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <QObject>
#include <QDirIterator>
#include <QDebug>

class NetworkInterface : public QObject
{
    Q_OBJECT
public:
    explicit NetworkInterface(QObject *parent = 0);
    static QStringList* getAllInterfaceNames();

signals:

public slots:

};

#endif // NETWORKINTERFACE_H
