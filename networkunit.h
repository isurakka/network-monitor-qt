#ifndef NETWORKUNIT_H
#define NETWORKUNIT_H

#endif // NETWORKUNIT_H

#include <QList>
#include <QStringList>

class NetworkUnit
{
private:
    QString displayName;
    unsigned long bytes;
public:
    NetworkUnit(QString displayName, unsigned long bytes)
    {
        this->displayName = displayName;
        this->bytes = bytes;
    }

    static QList<NetworkUnit> getSupportedUnits()
    {
        return QList<NetworkUnit>({
            NetworkUnit("B/s", 1UL),
            NetworkUnit("KB/s", 1000UL),
            NetworkUnit("MB/s", 1000000UL),
            NetworkUnit("GB/s", 1000000000UL),
        });
    }

    static QStringList getSupportedUnitNames()
    {
        QStringList ret;

        auto units = getSupportedUnits();
        for (auto unit : units)
        {
            ret.append(unit.displayName);
        }

        return ret;
    }
};
