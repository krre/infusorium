#pragma once
#include <QtCore>

class Net : public QObject
{
    Q_OBJECT
public:
    explicit Net(QObject *parent = 0);
    ~Net();
    Q_INVOKABLE void setPort(quint16 port);

private:
    QSharedMemory sharedMemory;
};
