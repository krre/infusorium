#include <QApplication>
#include <QtQml>
#include <registerosgtypes.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Aquarium");

    registerOsgTypes();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
