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

void World::run() {
    if (m_running) return;
    m_running = true;
    qDebug() << "Run World";
}

void World::stop() {
    if (!m_running) return;
    m_running = false;
    qDebug() << "Stop World";
}

void World::createFiles() {
    QJsonObject world;
    world["name"] = m_name;
    world["age"] = int(m_age);

    QFile file(m_dir + "/world.json");
    file.open(QIODeviceBase::WriteOnly);
    file.write(QJsonDocument(world).toJson());
}
