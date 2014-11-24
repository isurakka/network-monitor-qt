#include "applicationsettings.h"

ApplicationSettings::ApplicationSettings(QObject *parent) :
    QObject(parent)
{

}

NetworkInterface ApplicationSettings::getCurrentInterface()
{
    auto interfaceSelection = parent()->findChild<QObject*>("interfaceSelection");
    return NetworkInterface(interfaceSelection->property("currentText").toString());
}

NetworkUnit ApplicationSettings::getCurrentUnit()
{
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
