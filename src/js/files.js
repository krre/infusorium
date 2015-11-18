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
//    addRecentFile(filePath)
}
