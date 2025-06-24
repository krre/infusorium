#include "World.h"
#include <QDebug>

World::World(QObject* parent) : QObject(parent) {

}

void World::create(const QString& name, const QString& directory, quint32 age) {
    qDebug() << "name" << name << "directory" << directory << "age" << age;

    m_name = name;
    m_dir = name + "/" + directory;
    m_age = age;
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
