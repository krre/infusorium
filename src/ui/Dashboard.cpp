#include "Dashboard.h"
#include "widget/AutomaticSlider.h"
#include "world/World.h"
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>

Dashboard::Dashboard(const QString& name, const QString& directory, quint32 age) {
    m_world = new World(this);
    m_world->create(name, directory, age);
    createWidgets();
}

Dashboard::Dashboard(const QString& filePath) {
    m_world = new World(this);
    m_world->open(filePath);
    createWidgets();
}

World* Dashboard::world() const {
    return m_world;
}

void Dashboard::createWidgets() {
    auto ageSlider = new AutomaticSlider;
    ageSlider->setOrientation(Qt::Horizontal);
    ageSlider->setMaximum(m_world->age());
    ageSlider->setValue(m_world->today());

    auto ageSpinBox = new QSpinBox;
    ageSpinBox->setReadOnly(true);
    ageSpinBox->setValue(m_world->today());

    connect(ageSlider, &QSlider::valueChanged, ageSpinBox, &QSpinBox::setValue);
    connect(m_world, &World::todayChanged, ageSlider, &QSlider::setValue);

    auto ageLabel = new QLabel(QString::number(m_world->age()));

    auto ageLayout = new QHBoxLayout;
    ageLayout->addWidget(ageSlider, 1);
    ageLayout->addWidget(ageSpinBox);
    ageLayout->addWidget(ageLabel);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addStretch(1);
    verticalLayout->addLayout(ageLayout);

    setLayout(verticalLayout);
}
