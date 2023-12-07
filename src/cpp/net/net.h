#pragma once
#include <QObject>

class Net : public QObject
{
    Q_OBJECT
public:
    explicit Net(QObject *parent = 0);

private:
};
