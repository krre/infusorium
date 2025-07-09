#pragma once
#include <QWidget>

class World;

class Dashboard : public QWidget {
    Q_OBJECT
public:
    Dashboard(const QString& name, const QString& directory, quint32 age);
    Dashboard(const QString& filePath);

    World* world() const;

private:
    void createWidgets();

    World* m_world = nullptr;
};
