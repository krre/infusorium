#include "Process.h"
#include <Application.h>
#include <Settings.h>
#include <Utils.h>
#include <QApplication>
#include <QtQml>

int main(int argc, char* argv[]) {
    Application application(argc, argv);
    application.setApplicationName("Infusorium");
    application.setOrganizationName("Infusoria");
    application.setApplicationVersion("0.1.0");

    qmlRegisterType<Process>("Infusorium", 1, 0, "Process");

    Utils utils;
    Settings settings;

    if (settings.isEmpty()) {
        settings.setValue("Infusoria", "address", "localhost");
        settings.setValue("Infusoria", "port", "51000");
        settings.sync();
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("APP", &application);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return application.exec();
}
