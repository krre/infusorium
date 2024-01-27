#include "Process.h"
#include <Application.h>
#include <Settings.h>
#include <Utils.h>
#include <QApplication>
#include <QtQml>

int main(int argc, char* argv[]) {
    Application appication(argc, argv);
    appication.setApplicationName("Infusorium");

    qmlRegisterType<Process>("Infusorium", 1, 0, "Process");

    Utils utils;
    QString filePath = qApp->applicationDirPath() + "/aquarium.ini";
    Settings settings(filePath);

    if (!QFile::exists(filePath)) {
        settings.setValue("Infusoria", "address", "localhost");
        settings.setValue("Infusoria", "port", "51000");
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("APP", &appication);
    engine.rootContext()->setContextProperty("Settings", &settings);
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return appication.exec();
}
