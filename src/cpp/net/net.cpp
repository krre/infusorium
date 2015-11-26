#include "net.h"

Net::Net(QObject *parent) : QObject(parent), sharedMemory("infusoria")
{
}

Net::~Net()
{
    if (sharedMemory.isAttached()) {
        sharedMemory.detach();
    }
}

void Net::setPort(quint16 port)
{
    sharedMemory.attach();
    int maxNumPort = qPow(2, 16);
    bool isFirst = false;
    if (!sharedMemory.size()) {
        sharedMemory.create(sizeof(quint16) * maxNumPort);
        isFirst = true;
    }

    sharedMemory.lock();
    quint16* data = (quint16*)sharedMemory.data();

    if (isFirst) {
        data[0] = port;
        data[1] = 0;
    } else {
        for (int i = 0; i < maxNumPort; i++) {
            qDebug() << data[i];
            if (data[i] == 0) {
                data[i] = port;
                data[i + 1] = 0;
                break;
            }
        }
    }

    sharedMemory.unlock();
}
