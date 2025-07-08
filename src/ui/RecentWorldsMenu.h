#pragma once
#include <QMenu>

class RecentWorldsMenu : public QMenu {
    Q_OBJECT
public:
    RecentWorldsMenu(const QStringList& recentWorlds, QWidget* parent = nullptr);

    void addPath(const QString& path);
    QStringList recentWorlds() const;

signals:
    void activated(const QString& dir);

private slots:
    void clear();
};
