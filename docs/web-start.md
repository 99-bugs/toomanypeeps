# Solution for the START branch exercise

## HTML

Add the following HTML code to the `web/views/home.handlebars` file.

```HTML
<h1>Visitor statistics for: <span class="label">{{sensor_id}}</span></h1>

<h4>Number of People Currently in The Building:</h4>

<div class="counter-wrapper">
  <ul class="flip-counter huge" id="counter"></ul>
</div>

<canvas id="totalChart" ></canvas>
```

## JavaScript

Add the following JavaScript code to the `web/public/js/script.js` file.

```JavaScript
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
```
