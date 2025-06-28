#include "WorldController.h"
#include "world/World.h"

WorldController::WorldController(const QString& name, const QString& directory, quint32 age) {
    m_world = new World(this);
    m_world->create(name, directory, age);
}

WorldController::WorldController(const QString& directory) {
    m_world = new World(this);
    m_world->open(directory);
}

World* WorldController::world() const {
    return m_world;
}
