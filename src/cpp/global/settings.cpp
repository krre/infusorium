#include "settings.h"
#include "app.h"

Settings::Settings(QObject* parent) : QObject(parent)
{
    QString path = qApp->applicationDirPath() + QDir::separator() + QString("%1.ini").arg(App::name()).toLower();
    settings = new QSettings(path, QSettings::IniFormat, this);
    settings->setIniCodec("UTF-8");
}

void Settings::setValue(const QString& group, const QString& key, const QVariant& value)
{
    settings->beginGroup(group);
    settings->setValue(key, value);
    settings->endGroup();
}

QVariant Settings::value(const QString& group, const QString& key, const QVariant& defaultValue)
{
    return settings->value(QString("%1/%2").arg(group).arg(key), defaultValue);
}

void Settings::setMap(const QString& group, const QVariantMap& map)
{
    settings->beginGroup(group);
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        settings->setValue(i.key(), i.value());
    }
    settings->endGroup();
}

QVariantMap Settings::map(const QString& group)
{
    settings->beginGroup(group);
    QVariantMap map;
    QStringListIterator i(settings->allKeys());
    while (i.hasNext()) {
        QString key = i.next();
        map[key] = settings->value(key);
    }
    settings->endGroup();
    return map;
}
