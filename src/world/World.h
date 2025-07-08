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
    void save();

    QString filePath() const;

    bool isRunning() const;

    QString name() const;
    quint32 age() const;
    quint32 today() const;

public slots:
    void run();
    void stop();

signals:
    void runningChanged(bool running);
    void todayChanged(quint32 today);

private slots:
    void advance();

private:
    Database* m_database = nullptr;
    quint32 m_today = 0;
    bool m_running = false;
    QTimer* m_timer = nullptr;
};
