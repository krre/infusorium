#pragma once
#include <QMainWindow>

class FileSettings;
class RecentWorldsMenu;
class WorldController;

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

    void openWorld(const QString& dir);

    void showPreferences();
    void showAbout();

private:
    void readSettings();
    void writeSettings();

    void changeWindowTitle();
    void createActions();

    void resetWorld();

    FileSettings* m_fileSettings = nullptr;
    RecentWorldsMenu* m_recentWorldsMenu = nullptr;
    WorldController* m_worldController = nullptr;
};
