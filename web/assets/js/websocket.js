// Parameters
var hostname = "mqtt.99bugs.be";
var port = 1884;
var sensor_id = "demo";

// Create a client instance
var client = new Paho.MQTT.Client(hostname, Number(port), sensor_id + "-client");

// set callback handlers
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

// called when a message arrives
function onMessageArrived(message) {
    console.log("Message arrived: topic=" + message.destinationName + ", message=" + message.payloadString);
    update(Number(message.payloadString));
}
