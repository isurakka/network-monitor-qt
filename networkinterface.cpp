#include "networkinterface.h"

NetworkInterface::NetworkInterface(QObject *parent) :
    QObject(parent)
{
}

QStringList* NetworkInterface::getAllInterfaceNames()
{
    auto ret = new QStringList();

    QDirIterator it("/sys/class/net");
    while (it.hasNext()) {
        auto partialPath = it.next();
        auto fullPath = partialPath + "/statistics";
        qDebug() << fullPath;
        if (!QDir(fullPath).exists())
        {
            continue;
        }

        auto ifName = partialPath.right(partialPath.length() - 1 - partialPath.lastIndexOf(QChar('/')));
        ret->append(ifName);
    }

    return ret;
}
