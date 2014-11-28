#include "applicationsettings.h"

ApplicationSettings::ApplicationSettings(QStringList interfaceList, QStringList unitList, QObject *parent) :
    QObject(parent),
    currentInterfaceIndex(0),
    currentUnitIndex(2),
    interfaceList(interfaceList),
    unitList(unitList)
{

}

NetworkInterface ApplicationSettings::getCurrentInterface()
{
    return NetworkInterface(interfaceList[currentInterfaceIndex]);

    auto interfaceSelection = parent()->findChild<QObject*>("interfaceSelection");
    return NetworkInterface(interfaceSelection->property("currentText").toString());
}

NetworkUnit ApplicationSettings::getCurrentUnit()
{
    for (auto unit : NetworkUnit::getSupportedUnits())
    {
        if (unit.getDisplayName() == unitList[currentUnitIndex])
        {
            return unit;
        }
    }

    auto unitSelection = parent()->findChild<QObject*>("unitSelection");
    auto selectionText = unitSelection->property("currentText").toString();

    for (auto unit : NetworkUnit::getSupportedUnits())
    {
        if (unit.getDisplayName() == selectionText)
        {
            return unit;
        }
    }

    throw QString("Invalid selection");
}

int ApplicationSettings::getIndexForInterfaceName(QString name)
{
    int i = 0;
    for (auto it = interfaceList.begin(); it != interfaceList.end(); ++it)
    {
        if ((*it) == name)
        {
            return i;
        }

        i++;
    }
}

int ApplicationSettings::getIndexForUnitName(QString name)
{
    int i = 0;
    for (auto it = unitList.begin(); it != unitList.end(); ++it)
    {
        if ((*it) == name)
        {
            return i;
        }

        i++;
    }
}

void ApplicationSettings::interfaceSelectionChanged(int index)
{
    currentInterfaceIndex = index;

    QSettings qS;
    qS.setValue("interface", interfaceList[currentInterfaceIndex]);
}

void ApplicationSettings::unitSelectionChanged(int index)
{
    currentUnitIndex = index;

    QSettings qS;
    qS.setValue("unit", unitList[currentUnitIndex]);
}
