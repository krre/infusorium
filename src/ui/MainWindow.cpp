#include "MainWindow.h"
#include "RecentFilesMenu.h"
#include "Dashboard.h"
#include "core/Application.h"
#include "dialog/NewWorld.h"
#include "dialog/Preferences.h"
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
    NewWorld newWorld(m_fileSettings->worldWorkDirectory());

    if (newWorld.exec() == QDialog::Accepted) {
        close();
        m_dashboard = new Dashboard(newWorld.name(), newWorld.directory(), newWorld.age());
        setCentralWidget(m_dashboard);
        m_recentFilesMenu->addPath(m_dashboard->world()->filePath());
        emit worldOpenChanged(true);
        changeWindowTitle();
    }
}

void MainWindow::open() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open World"), m_fileSettings->worldWorkDirectory(),
                                                    tr("All Files (*);;Database Files (*.db)"));
    openWorld(filePath);
}

void MainWindow::close() {
    setCentralWidget(nullptr);
    delete m_dashboard;
    m_dashboard = nullptr;

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
    m_fileSettings->setMainWindowLastWorld(m_dashboard->world()->filePath());

    m_fileSettings->setRecentFiles(m_recentFilesMenu->recentFiles());
}

void MainWindow::changeWindowTitle() {
    QString title = Application::applicationName();

    if (m_dashboard) {
        title = m_dashboard->world()->name() + " - " + title;
    }

    setWindowTitle(title);
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &MainWindow::create);
    fileMenu->addAction(tr("Open..."), Qt::CTRL | Qt::Key_O, this, &MainWindow::open);

    m_recentFilesMenu = new RecentFilesMenu(m_fileSettings->recentFiles(), this);
    connect(m_recentFilesMenu, &RecentFilesMenu::activated, this, &MainWindow::openWorld);
    fileMenu->addAction(m_recentFilesMenu->menuAction());

    auto closeAction = fileMenu->addAction(tr("Close"), Qt::CTRL | Qt::Key_W, this, &MainWindow::close);
    closeAction->setEnabled(false);
    connect(this, &MainWindow::worldOpenChanged, closeAction, &QAction::setEnabled);

    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    auto editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Preferences..."), this, &MainWindow::showPreferences);

    auto worldMenu = menuBar()->addMenu(tr("World"));

    auto runWorldAction = worldMenu->addAction(tr("Run"));
    runWorldAction->setEnabled(false);

    auto stopWorldAction = worldMenu->addAction(tr("Stop"));
    stopWorldAction->setEnabled(false);

    auto resetWorldAction = worldMenu->addAction(tr("Reset"));
    resetWorldAction->setEnabled(false);

    connect(this, &MainWindow::worldOpenChanged, this, [=, this] (bool open) {
        runWorldAction->setEnabled(open && m_dashboard->world()->today() < m_dashboard->world()->age());
        resetWorldAction->setEnabled(open && !stopWorldAction->isEnabled());

        if (open) {
            connect(runWorldAction, &QAction::triggered, m_dashboard->world(), &World::run);
            connect(stopWorldAction, &QAction::triggered, m_dashboard->world(), &World::stop);
            connect(resetWorldAction, &QAction::triggered, this, &MainWindow::resetWorld);

            connect(m_dashboard->world(), &World::runningChanged, this, [=] (bool running) {
                runWorldAction->setEnabled(!running);
                stopWorldAction->setEnabled(running);
                resetWorldAction->setEnabled(!running);
            });
        }
    });

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);
}

void MainWindow::openWorld(const QString& filePath) {
    close();

    if (filePath.isEmpty()) return;
    if (!QFile::exists(filePath)) return;

    m_dashboard = new Dashboard(filePath);
    setCentralWidget(m_dashboard);
    m_recentFilesMenu->addPath(filePath);
    emit worldOpenChanged(true);
    changeWindowTitle();
}

void MainWindow::showPreferences() {
    Preferences preferences(m_fileSettings);
    preferences.exec();
}

void MainWindow::resetWorld() {
    if (QMessageBox::question(this, QString(), tr("Confirm to reset world"))) {
        m_dashboard->world()->reset();
    }
}
