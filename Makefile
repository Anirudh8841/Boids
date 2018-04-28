CXX = g++
IDIR = header
CFLAGS = -I$(IDIR)
ODIR = obj
LIBS = -lglut -lGLU -lGL
SRC = src
_DEPS = flock.h boids.h obstacle.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o boids.o flock.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_SRCS = boids.cpp flock.cpp main.cpp

SRCS = $(patsubst %,$(SRC)/%,$(_SRCS))


boids:$(SRCS) $(DEPS)
	$(CXX) -o $@ $(SRCS) $(CFLAGS) $(LIBS)
clean:
	rm -f boids $(ODIR)/*.o
