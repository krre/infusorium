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
    void fileOpenChanged(bool isOpen);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void create();
    void open();

    void openFile(const QString& filePath);
    void closeFile();

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
