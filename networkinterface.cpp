#include "networkinterface.h"

NetworkInterface::NetworkInterface(QString name) :
    name(name)
{

}

QStringList* NetworkInterface::getAllInterfaceNames()
{
    auto ret = new QStringList();

    QDirIterator it("/sys/class/net");
    while (it.hasNext()) {
        auto partialPath = it.next();
        auto fullPath = partialPath + "/statistics";

        if (!QDir(fullPath).exists())
        {
            continue;
        }

        auto ifName = partialPath.right(partialPath.length() - 1 - partialPath.lastIndexOf(QChar('/')));
        ret->append(ifName);
    }

    return ret;
}

quint64 NetworkInterface::getCurrentAmount(NetworkTransferType type)
{
    auto transferType = NetworkUnit::getStrForNetworkTransferType(type);

    auto statisticsFolder = "/sys/class/net/" + this->name + "/statistics";

    if (!QDir(statisticsFolder).exists())
    {
        throw QString("Statistics folder doesn't exists!");
    }

    auto transferFile = statisticsFolder + "/" + transferType + "_bytes";

    QFile file(transferFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw QString("Couldn't open the file for reading!");
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        auto line = in.readLine();
        bool ok;
        auto ret = line.toULongLong(&ok);

        if (!ok)
        {
            throw QString("Couldn't convert the value to integer");
        }

        return ret;
        break;
    }

    throw QString("Couldn't read the value!");
}

QString NetworkInterface::getName()
{
    return name;
}
