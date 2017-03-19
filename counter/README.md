# TooManyPeeps Counter service

This is a service for the TooManyPeeps application. Run this script to retain the
number of counted people per sensor.

The counter service will subscribe to the following MQTT topics:

`toomanypeeps/+/up`

`toomanypeeps/+/down`

`toomanypeeps/+/reset`

and will publish the value of the counter at the following MQTT topic:

`toomanypeeps/+/counter`

## Setup

Download or clone this repository.
Run the following command to install the service:

```
npm install
```
The service can be started by running the following command.

## Running the service

```
npm start
```

## Documentation

### Upcounter

To increse the count values for a specific sensor, you must publish a json object to the
`toomanypeeps/sensor_123/up` topic.

The json object must contain a value property with the count value assigned:

```json
{
  "value": 2
}
```

In this example, the counter will add 2 counts to the sensor with the name `sensor_123`

### Downcounter

To decrese the count values for a specific sensor, you must publish a json object to the
`toomanypeeps/sensor_123/down` topic.

The json object must contain a value property with the count value assigned:

```json
{
  "value": 2
}
```

In this example, the counter will subtract 2 counts to the sensor with the name `sensor_123`

### Reset

To reset a counter, you can publish the following json object to the `toomanypeeps/sensor_123/reset` topic:

```json
{
  "reset": true
}
```

### Counter

On any change to the counter values, the service will report the absolute value of the counter back to
anyone that is subscribed to the topic. The service will publish to the `toomanypeeps/sensor_123/counter` topic.

The message is formatted like this:

```json
{
  "value": 34
}
```

## Configuration

To get the service running, you must provide a settings file called `settings.json`.
In this settings file the hostname or ip-address, and the port of the MQTT server must be provided.
An example of the content of the file:

```json
{
    "mqtt": {
        "host": "mqtt.example.com",
        "port": 1883
    }
}
```

## Note

The service does not store any counter values. If the application is closed, the values will be lost.
