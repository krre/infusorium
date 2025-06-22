#pragma once
#include <QMainWindow>

class World;

class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void create();
    void showAbout();

private:
    void readSettings();
    void writeSettings();

    void createActions();

    World* m_world = nullptr;
};
