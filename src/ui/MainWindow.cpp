#include "MainWindow.h"
#include "core/Application.h"
#include "dialog/NewWorld.h"
#include "world/World.h"
#include "settings/FileSettings.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QSettings>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    m_fileSettings = new FileSettings(this);
    m_world = new World(this);
    changeWindowTitle();
    createActions();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::create() {
    NewWorld newWorld;

    if (newWorld.exec() == QDialog::Accepted) {
        m_world->create(newWorld.name(), newWorld.directory(), newWorld.age());
        changeWindowTitle();
    }
}

void MainWindow::open() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open World"));
    openWorld(dir);
}

void MainWindow::close() {
    m_world->close();
    changeWindowTitle();
}

void MainWindow::showAbout() {
    QMessageBox::about(this, tr("About %1").arg(Application::Name),
tr(R"(<h3>%1 %2</h3>
Environment for Infusoria artifical life units<br><br>
Based on Qt %3<br>
Build on %4 %5<br><br>
<a href=%6>%6</a><br><br>
Copyright © %7, Vladimir Zarypov)")
        .arg(Application::Name, Application::Version, QT_VERSION_STR,
        Application::BuildDate, Application::BuildTime, Application::Url, Application::Years));
}

void MainWindow::readSettings() {
    QByteArray geometry = m_fileSettings->mainWindowGeometry();

    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    restoreState(m_fileSettings->mainWindowState());
    openWorld(m_fileSettings->mainWindowLastWorld());
}

void MainWindow::writeSettings() {
    m_fileSettings->setMainWindowGeometry(saveGeometry());
    m_fileSettings->setMainWindowState(saveState());
    m_fileSettings->setMainWindowLastWorld(m_world->dir());
}

void MainWindow::changeWindowTitle() {
    QString title = Application::applicationName();

    if (!m_world->name().isEmpty()) {
        title = m_world->name() + " - " + title;
    }

    setWindowTitle(title);
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &MainWindow::create);
    fileMenu->addAction(tr("Open..."), Qt::CTRL | Qt::Key_O, this, &MainWindow::open);
    fileMenu->addAction(tr("Close"), Qt::CTRL | Qt::Key_W, this, &MainWindow::close);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    auto worldMenu = menuBar()->addMenu(tr("World"));
    worldMenu->addAction(tr("Run"), m_world, &World::run);
    worldMenu->addAction(tr("Stop"), m_world, &World::stop);

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);
}

void MainWindow::openWorld(const QString& dir) {
    if (dir.isEmpty()) return;
    if (!QDir().exists(dir)) return;

    m_world->open(dir);
    changeWindowTitle();
}
