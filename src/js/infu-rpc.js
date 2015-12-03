function send(message, id) {
    message.id = "aquarium-" + id
    mainRoot.webSocket.sendTextMessage(JSON.stringify(message))
}

function receive(message) {
    print("Infusoria:", message)
    var obj = JSON.parse(message)
    if (obj && obj.id) {
        if (obj.id === "aquarium-onlineList") {
            if (obj.result) {
                fillInfuModel(obj)
            }
        }
    }
}

function onlineList() {
    send({ method: "onlineList" }, "onlineList")
}

function fillInfuModel(obj) {
    infuModel.clear()
    for (var i in obj.result) {
        var path = obj.result[i]
        infuModel.append({ name: UTILS.pathToBaseName(path) })
    }
}
