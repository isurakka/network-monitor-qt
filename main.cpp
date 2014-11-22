#include <QApplication>
#include <QQmlApplicationEngine>
#include <QComboBox>
#include <QNetworkInterface>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto root = &engine;
    auto children = root->children();
    auto interfacesComboBox = root->findChild<QObject*>("interfaces");
    auto asd = root->findChild<QLabel*>("asd");

    auto allInterfaces = QNetworkInterface::allInterfaces();
    for (auto& interface : allInterfaces) {
        //interfacesComboBox->addItem(interface.name());
    }
    //interfacesComboBox->addItem();

    return app.exec();
}
