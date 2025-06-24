#pragma once
#include <QObject>

class World : public QObject {
public:
    World(QObject* parent);

    void create(const QString& name, const QString& directory, quint32 age);
    bool isRunning() const;

    QString name() const;
    quint32 age() const;

public slots:
    void run();
    void stop();

private:
    QString m_name;
    QString m_dir;
    quint32 m_age = 0;

    bool m_running = false;
};
