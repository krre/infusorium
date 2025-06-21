#pragma once
#include <QObject>

class World : public QObject {
public:
    World(QObject* parent);

    bool isRunning() const;

public slots:
    void run();
    void stop();

private:
    bool m_running = false;
};
