#pragma once
#include <QtCore>

class Utils : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString homePath READ homePath CONSTANT)

public:
    Q_INVOKABLE QString urlToPath(const QUrl& url) { return url.toLocalFile(); }
    Q_INVOKABLE QString urlToFileName(const QUrl& url) { return url.fileName(); }
    QString homePath() { return QStandardPaths::writableLocation(QStandardPaths::HomeLocation); }
};
