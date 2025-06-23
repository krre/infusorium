#pragma once
#include <QObject>

class World : public QObject {
public:
    World(QObject* parent);

    void create(const QString& name, const QString& directory, quint32 age);
    bool isRunning() const;

public slots:
    void run();
    void stop();

private:
    bool m_running = false;
};
