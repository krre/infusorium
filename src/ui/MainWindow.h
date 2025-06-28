#pragma once
#include <QMainWindow>

class FileSettings;
class World;

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
