#include "Settings.h"

namespace MainWindow {
    constexpr auto Geometry = "MainWindow/geometry";
    constexpr auto State = "MainWindow/state";
    constexpr auto LastWorld = "MainWindow/lastWorld";
}

namespace RecentWorlds {
    constexpr auto Dir = "RecentWorlds/dir";
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

void Settings::setRecentWorlds(const QStringList& recentWorlds) {
    QVariantList list;

    for (const auto& dir : recentWorlds) {
        list.append(dir);
    }

    setList(RecentWorlds::Dir, list);
}

QStringList Settings::recentWorlds() const {
    QStringList result;
    const QVariantList recentFiles = list(RecentWorlds::Dir);

    for (const auto& value : recentFiles) {
        result.append(value.toString());
    }

    return result;
}
