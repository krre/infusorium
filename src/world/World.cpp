#include "World.h"
#include "database/Database.h"
#include <QTimer>
#include <QDir>
#include <QJsonObject>

World::World(QObject* parent) : QObject(parent) {
    m_database = new Database(this);

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &World::advance);
}

World::~World() {
    stop();
}

void World::create(const QString& name, const QString& directory, quint32 age) {
    open(directory + "/" + name + ".db");
    m_database->updateMetaValue("name", name);
    m_database->updateMetaValue("age", age);
}

void World::open(const QString& filePath) {
    m_database->open(filePath);
    m_today = m_database->metaValue("today").toInt();
}

void World::reset() {
    m_today = 0;
    save();
    emit todayChanged(m_today);
}

void World::save() {
    m_database->updateMetaValue("today", m_today);
}

QString World::filePath() const {
    return m_database->filePath();
}

bool World::isRunning() const {
    return m_running;
}

QString World::name() const {
    return m_database->metaValue("name").toString();
}

quint32 World::age() const {
    return m_database->metaValue("age").toInt();
}

quint32 World::today() const {
    return m_today;
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
    save();
    emit runningChanged(false);
}

void World::advance() {
    m_today += 1;
    emit todayChanged(m_today);

    if (m_today == age()) {
        stop();
    }
}
