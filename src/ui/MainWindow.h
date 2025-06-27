#pragma once
#include <QMainWindow>

class FileSettings;
class World;

class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void create();
    void open();
    void close();

    void showAbout();

private:
    void readSettings();
    void writeSettings();

    void changeWindowTitle();
    void createActions();

    void openWorld(const QString& dir);

    FileSettings* m_fileSettings = nullptr;
    World* m_world = nullptr;
};
