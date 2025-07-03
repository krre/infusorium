#pragma once
#include <QObject>

class QTimer;

class World : public QObject {
    Q_OBJECT
public:
    World(QObject* parent);
    ~World();

    void create(const QString& name, const QString& directory, quint32 age);
    void open(const QString& directory);
    void close();
    void reset();

    bool isRunning() const;
    quint32 today() const;

    QString name() const;
    quint32 age() const;

    QString dir() const;

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
    QString worldFilePath() const;

    QByteArray toJson() const;
    void fromJson(const QByteArray& json);

    QString m_name;
    QString m_dir;
    quint32 m_age = 0;
    quint32 m_today = 0;

    bool m_running = false;
    QTimer* m_timer = nullptr;
};
