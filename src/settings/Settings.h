#pragma once
#include <QVariant>
#include <QSize>
#include <QColor>

class Settings {
public:
    void setMainWindowGeometry(const  QByteArray& geometry);
    QByteArray mainWindowGeometry() const;

    void setMainWindowState(const  QByteArray& state);
    QByteArray mainWindowState() const;

    void setMainWindowLastWorld(const QString& lastWorld);
    QString mainWindowLastWorld() const;

    void setRecentWorlds(const QStringList& recentWorlds);
    QStringList recentWorlds() const;

    void setWorldWorkDirectory(const QString& workDirectory);
    QString worldWorkDirectory() const;

protected:
    virtual void setValue(const QString& key, const QVariant& value) = 0;
    virtual QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const = 0;

    virtual void setList(const QString& key, const QVariantList& list) = 0;
    virtual QVariantList list(const QString& key) const = 0;
};
