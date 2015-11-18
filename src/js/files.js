.import "../js/dialog.js" as Dialog

function openUnit(filePath) {
    for (var i = 0; i < tabView.count; i++) {
        if (tabView.getTab(i).item.filePath === filePath) {
            tabView.currentIndex = i
            Dialog.errorMessage(qsTr("Unit already loaded"))
            return
        }
    }

    var unitName = UTILS.urlToFileName(filePath)
    var tab = tabView.addTab(unitName)
    tab.setSource("qrc:/qml/main/WorkArea.qml", { filePath: filePath })
    tabView.currentIndex = tabView.count - 1
    addRecentUnit(filePath)
}

function addRecentUnit(filePath) {
    var model = mainMenu.recentUnitsModel
    // Prevention of duplication of filePath and raising it on top.
    for (var i = 0; i < model.count; i++) {
        if (model.get(i).filePath === filePath) {
            model.remove(i)
        }
    }

    model.insert(0, { filePath: filePath })
    var maxRecentFiles = 10
    if (model.count === maxRecentFiles + 1) {
        model.remove(maxRecentFiles)
    }
}
