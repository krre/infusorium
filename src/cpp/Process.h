#pragma once
#include <QProcess>

class Process: public QProcess {
    Q_OBJECT
public:
    Process();
    Q_INVOKABLE void run(const QString& program, const QStringList& arguments);
    Q_INVOKABLE void shutdown() { close(); }

signals:
    void message(const QString& message);

private slots:
    void onReadyRead();
};
