#include "net/Net.h"
#include "Process.h"
#include <App.h>
#include <Settings.h>
#include <Utils.h>
#include <QApplication>
#include <QtQml>

int main(int argc, char* argv[]) {
    QApplication appication(argc, argv);
    appication.setApplicationName("Infusorium");
    appication.setApplicationVersion(App::version());

    qmlRegisterType<Process>("Infusorium", 1, 0, "Process");
    qmlRegisterType<Net>("Infusorium", 1, 0, "Net");

//    registerOsgTypes();

    App app;
    Utils utils;
    QString filePath = qApp->applicationDirPath() + "/aquarium.ini";
    Settings settings(filePath);
    if (!QFile::exists(filePath)) {
        settings.setValue("Infusoria", "address", "localhost");
        settings.setValue("Infusoria", "port", "51000");
    }

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("APP", &app);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("UTILS", &utils);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return appication.exec();
}
