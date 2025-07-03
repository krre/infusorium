#include "WorldController.h"
#include "widget/AutomaticSlider.h"
#include "world/World.h"
#include <QSpinBox>
#include <QVBoxLayout>

WorldController::WorldController(const QString& name, const QString& directory, quint32 age) {
    m_world = new World(this);
    m_world->create(name, directory, age);
    createWidgets();
}

WorldController::WorldController(const QString& directory) {
    m_world = new World(this);
    m_world->open(directory);
    createWidgets();
}

World* WorldController::world() const {
    return m_world;
}

void WorldController::createWidgets() {
    auto ageSlider = new AutomaticSlider;
    ageSlider->setOrientation(Qt::Horizontal);
    ageSlider->setMaximum(m_world->age());
    ageSlider->setValue(m_world->today());

    auto ageSpinBox = new QSpinBox;
    ageSpinBox->setReadOnly(true);
    ageSpinBox->setValue(m_world->today());

    connect(ageSlider, &QSlider::valueChanged, ageSpinBox, &QSpinBox::setValue);
    connect(m_world, &World::todayChanged, ageSlider, &QSlider::setValue);

    auto ageLayout = new QHBoxLayout;
    ageLayout->addWidget(ageSlider, 1);
    ageLayout->addWidget(ageSpinBox);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addStretch(1);
    verticalLayout->addLayout(ageLayout);

    setLayout(verticalLayout);
}
