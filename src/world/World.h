#pragma once
#include <QObject>

class Database;
class QTimer;

class World : public QObject {
    Q_OBJECT
public:
    World(QObject* parent);
    ~World();

    void create(const QString& name, const QString& directory, quint32 age);
    void open(const QString& filePath);
    void reset();
    QString filePath() const;

    bool isRunning() const;
    quint32 today() const;

    QString name() const;
    quint32 age() const;

public slots:
    void run();
    void stop();

signals:
    void runningChanged(bool running);
    void todayChanged(quint32 today);

private slots:
    void advance();

private:
    void save() const;

    Database* m_database = nullptr;

    quint32 m_age = 0;
    quint32 m_today = 0;

    bool m_running = false;
    QTimer* m_timer = nullptr;
};
