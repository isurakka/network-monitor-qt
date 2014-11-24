#ifndef NETWORKUNIT_H
#define NETWORKUNIT_H

#include <QList>
#include <QStringList>

enum NetworkTransferType
{
    Download,
    Upload,
};

class NetworkUnit
{
private:
    QString displayName;
    quint64 bytes;
public:
    NetworkUnit(QString displayName, quint64 bytes)
    {
        this->displayName = displayName;
        this->bytes = bytes;
    }

    QString getDisplayName()
    {
        return this->displayName;
    }

    quint64 getBytes()
    {
        return this->bytes;
    }

    static QList<NetworkUnit> getSupportedUnits()
    {
        return QList<NetworkUnit>({
            NetworkUnit("B", 1UL),
            NetworkUnit("KB", 1000UL),
            NetworkUnit("MB", 1000000UL),
            NetworkUnit("GB", 1000000000UL),
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

    static QString getStrForNetworkTransferType(NetworkTransferType type)
    {
        switch (type)
        {
            case NetworkTransferType::Download:
                return QString("rx");
            case NetworkTransferType::Upload:
                return QString("tx");
        }
    }
};

#endif // NETWORKUNIT_H
