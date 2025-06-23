#pragma once
#include "StandardDialog.h"

class BrowseLayout;
class QLineEdit;

class NewWorld : public StandardDialog {
    Q_OBJECT
public:
    NewWorld();

    QString name() const;
    QString directory() const;
    quint32 age() const;

private slots:
    void setOkButtonState();

private:
    QLineEdit* m_nameLineEdit = nullptr;
    BrowseLayout* m_directoryBrowseLayout = nullptr;
    QLineEdit* m_ageLineEdit = nullptr;
};
