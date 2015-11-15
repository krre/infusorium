#pragma once
#include <QtCore>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject* parent = 0);
    Q_INVOKABLE void setValue(const QString& group, const QString& key, const QVariant& value);
    Q_INVOKABLE QVariant value(const QString& group, const QString& key);

    Q_INVOKABLE void setMap(const QString& group, const QVariantMap& map);
    Q_INVOKABLE QVariantMap map(const QString& group);

private:
    QSettings* settings;

};