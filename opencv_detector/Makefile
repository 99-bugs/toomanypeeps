# The compiler to use
CC=$(CCPREFIX)g++

# Compiler flags
CFLAGS=-c -Wall `pkg-config --cflags opencv`
    # -c: Compile or assemble the source files, but do not link. The linking stage simply is not done. The ultimate output is in the form of an object file for each source file.
    # -Wall: This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.

LIBS=`pkg-config --libs opencv`

# Name of executable output
EXECUTABLE=peeps

all: clean $(EXECUTABLE)

$(EXECUTABLE): main.o camera.o web_camera.o filter_chain.o filter.o frame_grab.o gaussian_blur.o
	$(CC) main.o camera.o web_camera.o filter_chain.o filter.o frame_grab.o gaussian_blur.o -o $(EXECUTABLE) $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

camera.o: lib/camera/camera.cpp
	$(CC) $(CFLAGS) lib/camera/camera.cpp

web_camera.o: lib/camera/web_camera.cpp
	$(CC) $(CFLAGS) lib/camera/web_camera.cpp

filter_chain.o: lib/filter/filter_chain.cpp
	$(CC) $(CFLAGS) lib/filter/filter_chain.cpp

filter.o: lib/filter/filter.cpp
	$(CC) $(CFLAGS) lib/filter/filter.cpp

frame_grab.o: lib/filter/frame_grab.cpp
	$(CC) $(CFLAGS) lib/filter/frame_grab.cpp

gaussian_blur.o: lib/filter/gaussian_blur.cpp
	$(CC) $(CFLAGS) lib/filter/gaussian_blur.cpp

clean:
	rm -f *.o $(EXECUTABLE)
