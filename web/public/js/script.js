var mqtt;

$( document ).ready(function() {
  mqtt = new Paho.MQTT.Client("mqtt.99bugs.be",1884, "randomstringwithoutspaces");
  mqtt.onMessageArrived = onMessageArrived;
  mqtt.connect({ onSuccess: onConnect });
});

function onMessageArrived(message) {
  var json = JSON.parse(message.payloadString);
  var count = json.value;
  update(count);
}

function onConnect() {
  var sensor_id = $('meta[name=sensor-id]').attr("content");
  mqtt.subscribe("toomanypeeps/"+sensor_id+"/counter");
}
