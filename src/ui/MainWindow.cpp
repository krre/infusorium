#include "MainWindow.h"
#include "WorldController.h"
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
        m_worldController = new WorldController(newWorld.name(), newWorld.directory(), newWorld.age());
        emit worldOpenChanged(true);
        changeWindowTitle();
    }
}

void MainWindow::open() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open World"));
    openWorld(dir);
}

void MainWindow::close() {
    setCentralWidget(nullptr);
    delete m_worldController;
    m_worldController = nullptr;

    changeWindowTitle();
    emit worldOpenChanged(false);
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
    m_fileSettings->setMainWindowLastWorld(m_worldController->world()->dir());
}

void MainWindow::changeWindowTitle() {
    QString title = Application::applicationName();

    if (m_worldController) {
        title = m_worldController->world()->name() + " - " + title;
    }

    setWindowTitle(title);
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &MainWindow::create);
    fileMenu->addAction(tr("Open..."), Qt::CTRL | Qt::Key_O, this, &MainWindow::open);

    auto closeAction = fileMenu->addAction(tr("Close"), Qt::CTRL | Qt::Key_W, this, &MainWindow::close);
    closeAction->setEnabled(false);
    connect(this, &MainWindow::worldOpenChanged, closeAction, &QAction::setEnabled);

    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    auto worldMenu = menuBar()->addMenu(tr("World"));

    auto runWorldAction = worldMenu->addAction(tr("Run"));
    runWorldAction->setEnabled(false);

    auto stopWorldAction = worldMenu->addAction(tr("Stop"));
    stopWorldAction->setEnabled(false);

    connect(this, &MainWindow::worldOpenChanged, this, [=, this] (bool open) {
        runWorldAction->setEnabled(open);
        stopWorldAction->setEnabled(open);

        if (open) {
            connect(runWorldAction, &QAction::triggered, m_worldController->world(), &World::run);
            connect(stopWorldAction, &QAction::triggered, m_worldController->world(), &World::stop);
        }
    });

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);
}

void MainWindow::openWorld(const QString& dir) {
    close();

    if (dir.isEmpty()) return;
    if (!QDir().exists(dir)) return;

    m_worldController = new WorldController(dir);
    emit worldOpenChanged(true);
    changeWindowTitle();
}
