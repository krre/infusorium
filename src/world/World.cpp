#include "World.h"
#include <QTimer>
#include <QDir>
#include <QJsonObject>

World::World(QObject* parent) : QObject(parent) {
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &World::advance);
}

void World::create(const QString& name, const QString& directory, quint32 age) {
    m_name = name;
    m_dir = directory + "/" + name;
    m_age = age;

    QDir().mkpath(m_dir);
    createFiles();
    open(m_dir);
}

void World::open(const QString& directory) {
    m_dir = directory;

    QFile file(worldFilePath());
    file.open(QIODeviceBase::ReadOnly);

    fromJson(file.readAll());
}

void World::close() {
    m_name.clear();
    m_age = 0;
}

bool World::isRunning() const {
    return m_running;
}

quint32 World::today() const {
    return m_today;
}

QString World::name() const {
    return m_name;
}

quint32 World::age() const {
    return m_age;
}

QString World::dir() const {
    return m_dir;
}

void World::run() {
    if (m_running) return;

    m_timer->start();
    m_running = true;
    emit runningChanged(true);
}

void World::stop() {
    if (!m_running) return;

    m_timer->stop();
    m_running = false;
    emit runningChanged(false);
}

void World::advance() {
    m_today += 1;
    emit todayChanged(m_today);

    if (m_today == m_age) {
        stop();
    }
}

void World::createFiles() {
    QFile file(worldFilePath());
    file.open(QIODeviceBase::WriteOnly);
    file.write(toJson());
}

QString World::worldFilePath() const {
    return m_dir + "/world.json";
}

QByteArray World::toJson() const {
    QJsonObject world;
    world["name"] = m_name;
    world["age"] = int(m_age);

    return QJsonDocument(world).toJson();
}

void World::fromJson(const QByteArray& json) {
    QJsonObject world = QJsonDocument::fromJson(json).object();
    m_name = world["name"].toString();
    m_age = world["age"].toInt();
}
