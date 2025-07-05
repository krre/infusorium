#include "NewWorld.h"
#include "ui/widget/BrowseLayout.h"
#include "core/Utils.h"
#include <QLineEdit>
#include <QIntValidator>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <QDir>

NewWorld::NewWorld() {
    setWindowTitle(tr("New World"));

    m_nameLineEdit = new QLineEdit;
    connect(m_nameLineEdit, &QLineEdit::textChanged, this, &NewWorld::setOkButtonState);

    m_directoryBrowseLayout = new BrowseLayout;
    m_directoryBrowseLayout->lineEdit()->setText(Utils::workDir());
    connect(m_directoryBrowseLayout->lineEdit(), &QLineEdit::textChanged, this, &NewWorld::setOkButtonState);

    m_ageLineEdit = new QLineEdit;
    connect(m_ageLineEdit, &QLineEdit::textChanged, this, &NewWorld::setOkButtonState);

    auto validator = new QIntValidator(this);
    validator->setBottom(0);
    m_ageLineEdit->setValidator(validator);

    auto formLayout = new QFormLayout;
    formLayout->addRow(tr("Name:"), m_nameLineEdit);
    formLayout->addRow(tr("Directory:"), m_directoryBrowseLayout);
    formLayout->addRow(tr("Age:"), m_ageLineEdit);

    setContentLayout(formLayout);

    resizeToWidth(500);
    m_nameLineEdit->setFocus();
    setOkButtonState();
}

QString NewWorld::name() const {
    return m_nameLineEdit->text();
}

QString NewWorld::directory() const {
    return m_directoryBrowseLayout->lineEdit()->text();
}

quint32 NewWorld::age() const {
    return m_ageLineEdit->text().toUInt();
}

void NewWorld::accept() {
    if (QDir().exists(directory() + "/" + name())) {
        QMessageBox::critical(this, QString(), tr("World already exists!"));
    } else {
        StandardDialog::accept();
    }
}

void NewWorld::setOkButtonState() {
    bool isAllFieldsFilled = !(m_nameLineEdit->text().isEmpty() || m_directoryBrowseLayout->lineEdit()->text().isEmpty() || m_ageLineEdit->text().isEmpty());
    buttonBox()->button(QDialogButtonBox::Ok)->setEnabled(isAllFieldsFilled);
}
