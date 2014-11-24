#include <QApplication>
#include <QQmlApplicationEngine>
#include <QNetworkInterface>
#include <QComboBox>
#include <QStringListModel>
#include <QQmlContext>

#include <networkinterface.h>
#include <networkunit.h>
#include <overviewupdater.h>
#include "applicationsettings.h"
#include "networkgraph.h"
#include "networkupdater.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<NetworkGraph>("NetworkMonitor", 1, 0, "NetworkGraph");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto interfaceNameList = NetworkInterface::getAllInterfaceNames();
    QStringListModel interfacesModel;
    interfacesModel.setStringList(*interfaceNameList);
    engine.rootContext()->setContextProperty("interfacesModel", &interfacesModel);

    auto unitNameList = NetworkUnit::getSupportedUnitNames();
    QStringListModel unitsModel;
    unitsModel.setStringList(unitNameList);
    engine.rootContext()->setContextProperty("unitsModel", &unitsModel);

    auto root = engine.rootObjects().first();

    auto applicationSettings = new ApplicationSettings(root);
    auto overviewUpdater = new OverviewUpdater(root->findChild<QObject*>("overviewTab"), applicationSettings, root);
    auto networkUpdater = new NetworkUpdater(100, root);

    return app.exec();
}
