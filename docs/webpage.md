# Setting up the Webpage environment

Before starting the webserver, some dependencies need to be installed first.

Make sure you have NodeJs installed on your device or computer.

## Installing server dependencies

```
npm install
```

This will install the server code and other needed dependencies to run the application.

## Starging the server

The server can be started using an NPM command:

```
npm start
```

## Development dependencies

### Tools

`grunt-cli` and `bower` are required for development. You can install the following gems globally.

```
sudo npm install -g bower
```

```
sudo npm install -g grunt-cli
```

### JavaScript and CSS (SASS) dependencies

You can install the JavaScript and CSS dependencies using `bower` with the following command:

```
bower install
```

### Compiling assets

Assets (JavaScript and CSS) can be compiled into a public file with the following command:

```
grunt
```

Automatic recompilation of the assets files can be accomplished with a watch command:

```
grunt watch
```
