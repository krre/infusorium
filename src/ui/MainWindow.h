#pragma once
#include <QMainWindow>

class FileSettings;
class RecentFilesMenu;
class Dashboard;

class QAction;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

signals:
    void worldOpenChanged(bool open);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void create();
    void open();
    void close();

    void openWorld(const QString& filePath);

    void showPreferences();
    void showAbout();

private:
    void readSettings();
    void writeSettings();

    void changeWindowTitle();
    void createActions();

    void resetWorld();

    FileSettings* m_fileSettings = nullptr;
    RecentFilesMenu* m_recentFilesMenu = nullptr;
    Dashboard* m_dashboard = nullptr;
};
