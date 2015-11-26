#include <QApplication>
#include <QtQml>
#include <registerosgtypes.h>
#include "global/app.h"
#include "global/settings.h"
#include "global/utils.h"
#include "net/net.h"
#include "process.h"

int main(int argc, char* argv[])
{
    QApplication appication(argc, argv);
    appication.setApplicationName(App::name());
    appication.setApplicationVersion(App::version());

    qmlRegisterType<Process>("Aquarium", 1, 0, "Process");
    qmlRegisterType<Net>("Aquarium", 1, 0, "Net");

    registerOsgTypes();

    App app;
    Settings settings;
    Utils utils;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("APP", &app);
    engine.rootContext()->setContextProperty("SETTINGS", &settings);
    engine.rootContext()->setContextProperty("UTILS", &utils);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return appication.exec();
}
