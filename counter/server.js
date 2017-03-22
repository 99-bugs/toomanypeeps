
var settings = require('./settings.json')
var mqtt  = require('mqtt').connect({ host: settings.mqtt.host, port: settings.mqtt.port })

var state = {}

//mqtt.publish(topic, message, {retain: true})

mqtt.on('connect', function () {
    console.log("MQTT connected");
    mqtt.subscribe('toomanypeeps/+/up');
    mqtt.subscribe('toomanypeeps/+/down');
    mqtt.subscribe('toomanypeeps/+/reset');
});

mqtt.on('message', function(topic, message) {
    console.log("Message received " + topic + ": " + message);
    var sensor_id = topic.split('/')[1];
    var command = topic.split('/')[2];
    message = JSON.parse(message)
    if(state[sensor_id] == null) { state[sensor_id] = 0;}
    switch(command) {
        case 'up':
            state[sensor_id] += message.value
            break;
        case 'down':
            state[sensor_id] -= message.value
            break;
        case 'reset':
            if(message.reset){
              state[sensor_id] = 0
            }
            break;
        default:
    }
    mqtt.publish(
      'toomanypeeps/' + sensor_id + '/counter',
       JSON.stringify({value: state[sensor_id]}),
        {retain: true}
      )
});
