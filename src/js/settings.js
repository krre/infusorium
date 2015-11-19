function save() {
    saveGeometry()
    saveRecentFiles()
}

function load() {
    loadGeometry()
    loadRecentFiles()
}

function saveGeometry() {
    SETTINGS.setMap("MainWindow", {
        x: x,
        y: y,
        width: width,
        height: height
    })
}

function loadGeometry() {
    var geometry = SETTINGS.map("MainWindow")
    if (Object.keys(geometry).length) {
        x = geometry.x
        y = geometry.y
        width = geometry.width
        height = geometry.height
    } else {
        if (Screen.width && Screen.height) {
            x = (Screen.width - width) / 2
            y = (Screen.height - height) / 2
        } else {
            x = 200
            y = 200
        }
    }
}

function saveRecentFiles() {
    var model = mainMenu.recentFilesModel
    var list = []
    for (var i = 0; i < model.count; i++) {
        var filePath = model.get(i).filePath
        if (filePath) {
            list.push(filePath)
        }
    }
    SETTINGS.setList("RecentFiles", list)
}

function loadRecentFiles() {
    var list = SETTINGS.list("RecentFiles")
    var model = mainMenu.recentFilesModel
    for (var i = 0; i < list.length; i++) {
        var filePath = list[i]
        if (UTILS.isFileExists(filePath)) {
            model.append({ filePath: filePath })
        }
    }
}
