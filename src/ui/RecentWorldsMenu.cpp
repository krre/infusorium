#include "RecentWorldsMenu.h"
#include <QFile>

constexpr auto SystemActionCount = 2;
constexpr auto MaxActionCount = 10;

RecentWorldsMenu::RecentWorldsMenu(const QStringList& recentWorlds, QWidget* parent)
    : QMenu(tr("Recent Worlds"), parent) {
    addSeparator();
    addAction(tr("Clear"), this, &RecentWorldsMenu::clear);

    for (const QString& path : recentWorlds) {
        addPath(path);
    }
}

void RecentWorldsMenu::addPath(const QString& path) {
    if (path.isEmpty()) return;
    if (!QFile::exists(path)) return;
    const auto pathActions = actions();

    for (QAction* action : pathActions) {
        if (action->text() == path) {
            removeAction(action);
        }
    }

    auto pathAction = new QAction(path);
    connect(pathAction, &QAction::triggered, this, [=, this] {
        emit activated(path);
    });

    insertAction(actions().constFirst(), pathAction);

    if (actions().size() > MaxActionCount + SystemActionCount) {
        removeAction(actions().at(actions().size() - SystemActionCount - 1));
    }
}

QStringList RecentWorldsMenu::recentWorlds() const {
    QStringList result;

    for (int i = 0; i < actions().size() - SystemActionCount; ++i) {
        result.append(actions().at(i)->text());
    }

    return result;
}

void RecentWorldsMenu::clear() {
    for (int i = actions().size() - SystemActionCount - 1; i >= 0; --i) {
        removeAction(actions().at(i));
    }
}
