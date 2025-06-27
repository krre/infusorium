#include "Settings.h"

namespace MainWindow {
    constexpr auto Geometry = "MainWindow/geometry";
    constexpr auto State = "MainWindow/state";
    constexpr auto LastWorld = "MainWindow/lastWorld";
}

void Settings::setMainWindowGeometry(const QByteArray& geometry) {
    setValue(MainWindow::Geometry, geometry);
}

QByteArray Settings::mainWindowGeometry() const {
    return value(MainWindow::Geometry).toByteArray();
}

void Settings::setMainWindowState(const QByteArray& state) {
    setValue(MainWindow::State, state);
}

QByteArray Settings::mainWindowState() const {
    return value(MainWindow::State).toByteArray();
}

void Settings::setMainWindowLastWorld(const QString& lastWorld) {
    setValue(MainWindow::LastWorld, lastWorld);
}

QString Settings::mainWindowLastWorld() const {
    return value(MainWindow::LastWorld).toString();
}
