#include "RecentWorldsMenu.h"
#include <QFile>

constexpr auto SystemActionCount = 2;
constexpr auto MaxActionCount = 10;

RecentWorldsMenu::RecentWorldsMenu(const QStringList& recentWorlds, QWidget* parent)
    : QMenu(tr("Recent Worlds"), parent) {
    addSeparator();
    addAction(tr("Clear"), this, &RecentWorldsMenu::clear);

    for (const QString& dir : recentWorlds) {
        addDir(dir);
    }
}

void RecentWorldsMenu::addDir(const QString& dir) {
    if (dir.isEmpty()) return;
    if (!QFile::exists(dir)) return;
    const auto dirActions = actions();

    for (QAction* action : dirActions) {
        if (action->text() == dir) {
            removeAction(action);
        }
    }

    auto dirAction = new QAction(dir);
    connect(dirAction, &QAction::triggered, this, [=, this] {
        emit activated(dir);
    });

    insertAction(actions().constFirst(), dirAction);

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
