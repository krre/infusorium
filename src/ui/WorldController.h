#pragma once
#include <QWidget>

class World;

class WorldController : public QWidget {
    Q_OBJECT
public:
    WorldController(const QString& name, const QString& directory, quint32 age);
    WorldController(const QString& filePath);

    World* world() const;

private:
    void createWidgets();

    World* m_world = nullptr;
};
