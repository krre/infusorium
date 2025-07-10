#include "Settings.h"
#include "core/Utils.h"

namespace MainWindow {
    constexpr auto Geometry = "MainWindow/geometry";
    constexpr auto State = "MainWindow/state";
    constexpr auto LastFile = "MainWindow/lastFile";
}

namespace RecentFiles {
    constexpr auto Path = "RecentFiles/path";
}

namespace World {
    constexpr auto WorkDirectory = "World/workDirectory";
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

void Settings::setMainWindowLastFile(const QString& lastFile) {
    setValue(MainWindow::LastFile, lastFile);
}

QString Settings::mainWindowLastFile() const {
    return value(MainWindow::LastFile).toString();
}

void Settings::setRecentFiles(const QStringList& recentFiles) {
    QVariantList list;

    for (const auto& path : recentFiles) {
        list.append(path);
    }

    setList(RecentFiles::Path, list);
}

QStringList Settings::recentFiles() const {
    QStringList result;
    const QVariantList recentFiles = list(RecentFiles::Path);

    for (const auto& value : recentFiles) {
        result.append(value.toString());
    }

    return result;
}

void Settings::setWorldWorkDirectory(const QString& workDirectory) {
    setValue(World::WorkDirectory, workDirectory);
}

QString Settings::worldWorkDirectory() const {
    return value(World::WorkDirectory, Utils::workDir()).toString();
}
