#include <QApplication>
#include <QtQml>
//#include <registerosgtypes.h>
#include <app.h>
#include <settings.h>
#include <utils.h>
#include "net/net.h"
#include "process.h"

int main(int argc, char* argv[])
{
    QApplication appication(argc, argv);
    appication.setApplicationName("Aquarium");
    appication.setApplicationVersion(App::version());

    qmlRegisterType<Process>("Aquarium", 1, 0, "Process");
    qmlRegisterType<Net>("Aquarium", 1, 0, "Net");

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
    engine.rootContext()->setContextProperty("SETTINGS", &settings);
    engine.rootContext()->setContextProperty("UTILS", &utils);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return appication.exec();
}
