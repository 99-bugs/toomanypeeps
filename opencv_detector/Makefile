# The compiler to use
CC=$(CCPREFIX)g++
LD=ld

# Compiler flags
CFLAGS=-c -Wall `pkg-config --cflags opencv`
    # -c: Compile or assemble the source files, but do not link. The linking stage simply is not done. The ultimate output is in the form of an object file for each source file.
    # -Wall: This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.

LIBS=`pkg-config --libs opencv`

TARGET=peeps
SRCDIR=src
BUILDDIR=build

# OBJ := $(patsubst %.cpp,%.o,$(shell find ./src -name '*.cpp'))
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(shell find ./$(SRCDIR) -name '*.cpp'))

all: $(TARGET)

peeps : $(OBJ)
	$(CC) $(LDFLAGS) -o $(BUILDDIR)/$@ $(OBJ) $(LIBS)

%.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(BUILDDIR)/$(TARGET)
