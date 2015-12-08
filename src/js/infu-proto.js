function send(message) {
    message.sender = "aquarium"
    mainRoot.webSocket.sendTextMessage(JSON.stringify(message))
}

function receive(message) {
//    print("Infusoria:", message)
    var obj = JSON.parse(message)
    if (obj) {
        if (obj.info) {
            if (obj.info === "log") {
                infuManager.log(obj.value)
            }

        } else if (obj.action) {
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
}

function getInfusories() {
    send({ action: "getInfusories" })
}

function fillInfuModel(obj) {
    infuModel.clear()
    for (var i in obj.result) {
        infuModel.append({ name: obj.result[i].name, uuid: obj.result[i].uuid })
    }
}

function getLog(value) {
    send({ action: "getLog", options: { enable: value } })
}
