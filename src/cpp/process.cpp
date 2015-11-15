#include "process.h"

Process::Process()
{
    setProcessChannelMode(QProcess::MergedChannels);
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Process::run(const QString& program, const QStringList& arguments)
{
    message(program + " " + arguments.join(" "));
    if (arguments.count()) {
        start(program, arguments);
    } else {
        start(program);
    }
}

void Process::onReadyRead()
{
    emit message(readAllStandardOutput());
}
