#include "World.h"
#include <QDebug>

World::World(QObject* parent) : QObject(parent) {

}

bool World::isRunning() const {
    return m_running;
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
