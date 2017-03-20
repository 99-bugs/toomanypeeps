// Parameters
var hostname = "mqtt.99bugs.be";
var port = 1884;

const sensor_id = "demo";

// Create a client instance
var client = new Paho.MQTT.Client(hostname, Number(port), "clientId");

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({
    onSuccess: onConnect
});


// called when the client connects
function onConnect() {
    // Once a connection has been made, make a subscription and send a message.
    console.log("onConnect");
    client.subscribe("toomanypeeps/"+sensor_id+"/counter");
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
        console.log("onConnectionLost:" + responseObject.errorMessage);
    }
}

// called when a message arrives
function onMessageArrived(message) {
    console.log("Message arrived: topic=" + message.destinationName + ", message=" + message.payloadString);
    update(JSON.parse(message.payloadString).value);
}

function send() {
    if (!client) {
        return;
    }
    var message = new Paho.MQTT.Message("Hello");
    message.destinationName = "/World";
    client.send(message);
}
