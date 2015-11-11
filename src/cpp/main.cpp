#include <QApplication>
#include <QtQml>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Aquarium");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
