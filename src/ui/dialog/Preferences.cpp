#include "Preferences.h"
#include "ui/widget/BrowseLayout.h"
#include "settings/Settings.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QFormLayout>

Preferences::Preferences(Settings* settings) : m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    auto workDirLayout = new BrowseLayout(settings->worldWorkDirectory());
    m_worldDirLineEdit = workDirLayout->lineEdit();

    auto worldLayout = new QFormLayout;
    worldLayout->addRow(tr("Work directory:"), workDirLayout);

    auto worldGroupBox = new QGroupBox(tr("World"));
    worldGroupBox->setLayout(worldLayout);

    setContentWidget(worldGroupBox);

    resizeToWidth(500);
    readSettings();
}

void Preferences::accept() {
    writeSettings();
    StandardDialog::accept();
}

void Preferences::readSettings() {
}

void Preferences::writeSettings() {
    m_settings->setWorldWorkDirectory(m_worldDirLineEdit->text());
}
