#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <QVariant>

#include "networkinterface.h"
#include "networkunit.h"

class ApplicationSettings : public QObject
{
    Q_OBJECT

private:
    int currentInterfaceIndex;
    QStringList interfaceList;
    int currentUnitIndex;
    QStringList unitList;

public:
    explicit ApplicationSettings(QStringList interfaceList, QStringList unitList, QObject *parent = 0);
    NetworkInterface getCurrentInterface();
    NetworkUnit getCurrentUnit();

signals:

private slots:
    void interfaceSelectionChanged(int index);
    void unitSelectionChanged(int index);

public slots:

};

#endif // APPLICATIONSETTINGS_H
