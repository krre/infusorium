#include <QApplication>
#include <QtQml>
#include <registerosgtypes.h>
#include "global/app.h"
#include "global/settings.h"

int main(int argc, char* argv[])
{
    QApplication appication(argc, argv);
    appication.setApplicationName(App::name());
    appication.setApplicationVersion(App::version());

    registerOsgTypes();

    App app;
    Settings settings;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("APP", &app);
    engine.rootContext()->setContextProperty("SETTINGS", &settings);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return appication.exec();
}
