#pragma once
#include "StandardDialog.h"

class BrowseLayout;
class QLineEdit;

class NewWorld : public StandardDialog {
    Q_OBJECT
public:
    NewWorld(const QString& workDir);

    QString name() const;
    QString directory() const;
    quint32 age() const;

public slots:
    void accept() override;

private slots:
    void setOkButtonState();

private:
    QLineEdit* m_nameLineEdit = nullptr;
    BrowseLayout* m_directoryBrowseLayout = nullptr;
    QLineEdit* m_ageLineEdit = nullptr;
};
