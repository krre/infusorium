#include "World.h"
#include <QDir>
#include <QJsonObject>
#include <QDebug>

World::World(QObject* parent) : QObject(parent) {

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

    QJsonObject world = QJsonDocument::fromJson(file.readAll()).object();
    m_name = world["name"].toString();
    m_age = world["age"].toInt();
}

void World::close() {
    m_name.clear();
    m_age = 0;
}

bool World::isRunning() const {
    return m_running;
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
    m_running = true;
    runningChanged(true);
    qDebug() << "Run World";
}

void World::stop() {
    if (!m_running) return;
    m_running = false;
    runningChanged(false);
    qDebug() << "Stop World";
}

void World::createFiles() {
    QJsonObject world;
    world["name"] = m_name;
    world["age"] = int(m_age);

    QFile file(worldFilePath());
    file.open(QIODeviceBase::WriteOnly);
    file.write(QJsonDocument(world).toJson());
}

QString World::worldFilePath() const {
    return m_dir + "/world.json";
}
