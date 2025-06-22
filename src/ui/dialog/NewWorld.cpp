#include "NewWorld.h"
#include <QLineEdit>
#include <QIntValidator>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QPushButton>

NewWorld::NewWorld() {
    setWindowTitle(tr("New World"));

    m_nameLineEdit = new QLineEdit;
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &NewWorld::setOkButtonState);

    m_ageLineEdit = new QLineEdit;
    connect(m_ageLineEdit, &QLineEdit::textChanged, this, &NewWorld::setOkButtonState);

    auto validator = new QIntValidator(this);
    validator->setBottom(0);
    m_ageLineEdit->setValidator(validator);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Age:"), m_ageLineEdit);

    setContentLayout(formLayout);

    resizeToWidth(400);
    m_nameLineEdit->setFocus();
    setOkButtonState();
}

QString NewWorld::name() const {
    return m_nameLineEdit->text();
}

quint32 NewWorld::age() const {
    return m_ageLineEdit->text().toUInt();
}

void NewWorld::setOkButtonState() {
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(!(m_nameLineEdit->text().isEmpty() || m_ageLineEdit->text().isEmpty()));
}
