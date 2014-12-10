#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <QVariant>
#include <QSettings>
#include <QQuickItem>
#include <QSettings>

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
    int getIndexForInterfaceName(QString name);
    int getIndexForUnitName(QString name);
    NetworkUnit getUnitForIndex(int index);

signals:

public slots:
    void interfaceSelectionChanged(int index);
    void unitSelectionChanged(int index);

    void quotaEnabledChanged();
    void quotaTypeChanged(int index);
    void quotaAmountChanged();
    void quotaUnitChanged(int index);
};

#endif // APPLICATIONSETTINGS_H
