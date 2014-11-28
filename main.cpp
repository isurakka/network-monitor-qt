#include <QApplication>
#include <QQmlApplicationEngine>
#include <QNetworkInterface>
#include <QComboBox>
#include <QStringListModel>
#include <QQmlContext>
#include <QQuickView>
#include <QSortFilterProxyModel>
#include <QTableView>

#include <networkinterface.h>
#include <networkunit.h>
#include "applicationsettings.h"
#include "networkgraph.h"
#include "networkupdater.h"
#include "hourlymodel.h"

int main(int argc, char *argv[])
{
    //QCoreApplication::setOrganizationName("Syneh");
    QCoreApplication::setApplicationName("network-monitor");

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

    auto quotaMethodList = QStringList({
        QString("Last 24 hours"),
        QString("Day"),
        QString("Month"),
    });
    QStringListModel quotaModel;
    quotaModel.setStringList(quotaMethodList);
    engine.rootContext()->setContextProperty("quotaModel", &quotaModel);

    auto root = engine.rootObjects().first();

    auto applicationSettings = new ApplicationSettings(*interfaceNameList, unitNameList, root);

    QSettings qS;

    auto interfaceSelection = root->findChild<QQuickItem*>("interfaceSelection");
    QObject::connect(interfaceSelection, SIGNAL(activated(int)),
                          applicationSettings, SLOT(interfaceSelectionChanged(int)));
    interfaceSelection->setProperty("currentIndex", applicationSettings->getIndexForInterfaceName(qS.value("interface").toString()));


    auto unitSelection = root->findChild<QQuickItem*>("unitSelection");
    QObject::connect(unitSelection, SIGNAL(activated(int)),
                          applicationSettings, SLOT(unitSelectionChanged(int)));
    unitSelection->setProperty("currentIndex", applicationSettings->getIndexForUnitName(qS.value("unit").toString()));

    auto networkStorage = new NetworkStorage(root);
    auto networkUpdater = new NetworkUpdater(1000, &engine, applicationSettings, networkStorage, root);

    for (auto& graph : root->findChildren<NetworkGraph*>())
    {
        graph->settings = applicationSettings;
        graph->snapshots = &networkUpdater->snapshots;

        if (graph->objectName() == "downloadGraph")
        {
            graph->type = NetworkTransferType::Download;
            graph->color = QColor("#27ae60");
        }
        else if (graph->objectName() == "uploadGraph")
        {
            graph->type = NetworkTransferType::Upload;
            graph->color = QColor("#c0392b");
        }
    }

    auto tableView = root->findChild<QTableView*>();

    auto hourlyModel = new HourlyModel(applicationSettings, networkStorage, root);

    auto proxyModel = new QSortFilterProxyModel(root);
    proxyModel->setSourceModel(hourlyModel);
    proxyModel->setDynamicSortFilter(true);

    // TODO: Sorting doesn't work
    engine.rootContext()->setContextProperty("hourlyModel", proxyModel);

    QObject::connect(interfaceSelection, SIGNAL(activated(int)),
                          networkUpdater, SLOT(interfaceSelectionChanged(int)));

    QObject::connect(unitSelection, SIGNAL(activated(int)),
                          networkUpdater, SLOT(unitSelectionChanged(int)));

    return app.exec();
}
