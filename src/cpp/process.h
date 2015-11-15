#pragma once
#include <QtCore>

class Process: public QProcess
{
    Q_OBJECT
public:
    Process();
    Q_INVOKABLE void run(const QString& program, const QStringList& arguments);

signals:
    void message(const QString& message);

private slots:
    void onReadyRead();
};
