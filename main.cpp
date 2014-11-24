#include <QApplication>
#include <QQmlApplicationEngine>
#include <QNetworkInterface>
#include <QComboBox>
#include <QStringListModel>
#include <QQmlContext>

#include <networkinterface.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto interfaceNameList = NetworkInterface::getAllInterfaceNames();

    QStringListModel interfacesModel;
    interfacesModel.setStringList(*interfaceNameList);
    engine.rootContext()->setContextProperty("interfacesModel", &interfacesModel);

    return app.exec();
}
