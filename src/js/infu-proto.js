function send(message) {
    message.sender = "aquarium"
    mainRoot.webSocket.sendTextMessage(JSON.stringify(message))
}

function receive(message) {
//    print("Infusoria:", message)
    var obj = JSON.parse(message)
    if (obj) {
        if (obj.action === "getInfusories") {
            if (obj.result) {
                fillInfuModel(obj)
            }
        } else if (obj.action === "getLog") {
            for (var i in obj.result) {
                infuManager.log(obj.result[i])
            }
        }
    }
}

function getInfusories() {
    send({ action: "getInfusories" })
}

function fillInfuModel(obj) {
    infuModel.clear()
    for (var i in obj.result) {
        var path = obj.result[i]
        infuModel.append({ name: UTILS.pathToBaseName(path) })
    }
}

function getLog(value) {
    send({ action: "getLog", options: { enable: value } })
}
