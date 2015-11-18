function save() {
    geometrySave()
}

function load() {
    geometryLoad()
}

function geometrySave() {
    SETTINGS.setMap("MainWindow", {
        x: x,
        y: y,
        width: width,
        height: height
    })
}

function geometryLoad() {
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

