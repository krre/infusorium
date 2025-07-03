#pragma once
#include <QMenu>

class RecentWorldsMenu : public QMenu {
    Q_OBJECT
public:
    RecentWorldsMenu(const QStringList& recentWorlds, QWidget* parent = nullptr);

    void addDir(const QString& dir);
    QStringList recentWorlds() const;

signals:
    void activated(const QString& dir);

private slots:
    void clear();
};
