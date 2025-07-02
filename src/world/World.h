#pragma once
#include <QObject>

class World : public QObject {
    Q_OBJECT
public:
    World(QObject* parent);

    void create(const QString& name, const QString& directory, quint32 age);
    void open(const QString& directory);
    void close();

    bool isRunning() const;

    QString name() const;
    quint32 age() const;

    QString dir() const;

public slots:
    void run();
    void stop();

signals:
    void runningChanged(bool running);

private:
    void createFiles();
    QString worldFilePath() const;

    QString m_name;
    QString m_dir;
    quint32 m_age = 0;

    bool m_running = false;
};
