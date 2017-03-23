var mqtt;
var sensor_id;

$( document ).ready(function() {

  sensor_id = $('meta[name=sensor-id]').attr("content");

  console.log("Sensor id: " + sensor_id);

  mqtt = new Paho.MQTT.Client("mqtt.99bugs.be",1884, "randomstringwithoutspaces");
  mqtt.onMessageArrived = onMessageArrived;
  mqtt.connect({
      onSuccess: onConnect
  });

});

function onMessageArrived(message) {
  console.log("Message arrived: topic=" + message.destinationName + ", message=" + message.payloadString);
  var json = JSON.parse(message.payloadString);
  var count = json.value;
  update(count);
}

function onConnect() {
  console.log("MQTT connected");
  console.log("toomanypeeps/"+sensor_id+"/counter");
  mqtt.subscribe("toomanypeeps/"+sensor_id+"/counter");
}

/************************************************************/

$( document ).ready(function() {
  $(document).foundation();

  window.myCounter = new flipCounter('counter');

});

var update = function(value){
  console.log("Update value: " + value);
  window.Chart.addData(value);
  window.myCounter.setValue(value);
}
