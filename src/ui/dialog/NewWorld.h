#pragma once
#include "StandardDialog.h"

class QLineEdit;

class NewWorld : public StandardDialog {
    Q_OBJECT
public:
    NewWorld();

    QString name() const;
    quint32 age() const;

private slots:
    void setOkButtonState();

private:
    QLineEdit* m_nameLineEdit = nullptr;
    QLineEdit* m_ageLineEdit = nullptr;
};
