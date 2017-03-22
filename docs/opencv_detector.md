# OpenCV C++ Detector App

## Extra information

* [Background extraction](http://docs.opencv.org/3.1.0/d1/dc5/tutorial_background_subtraction.html)

## Dependencies

* [Install OpenCV on Raspberry Pi 3](opencv_raspberry_pi_3.md)
* [Install OpenCV on Ubuntu](opencv_ubuntu.md)
* [Install Mqtt](mqtt.md)
* [Install RaspiCam](raspi_cam.md)

## Cloning the project

```shell
cd
git clone https://github.com/99-bugs/toomanypeeps.git
```

To start your own code project checkout the start branch

```shell
cd toomanypeeps
git checkout start
```

## Compiling the OpenCV C++ app

Just execute a `make USE_PI=1` inside the *opencv_detector* directory:

```shell
cd toomanypeeps
cd opencv_detector
make USE_PI=1
```

## Compiling the OpenCV C++ app for development system

Just execute a `make` inside the *opencv_detector* directory:

```shell
cd opencv_detector
make
```

## Running the OpenCV C++ app

To run the application stay in the `opencv_detector` directory and run

```shell
./bin/peeps
```
