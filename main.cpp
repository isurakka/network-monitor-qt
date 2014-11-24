#include <QApplication>
#include <QQmlApplicationEngine>
#include <QNetworkInterface>
#include <QComboBox>
#include <QStringListModel>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QStringList interfaceNameList;

    auto allInterfaces = QNetworkInterface::allInterfaces();
    for (auto& interface : allInterfaces) {
        interfaceNameList.append(interface.name());
    }

    QStringListModel interfacesModel;
    interfacesModel.setStringList(interfaceNameList);
    engine.rootContext()->setContextProperty("interfacesModel", &interfacesModel);

    return app.exec();
}
