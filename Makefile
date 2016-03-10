CPP = g++ -std=c++11 -Wall -pedantic

CPP_DEBUG = @$(CPP) -g
CPP_RELEASE = @$(CPP) -O2 -march=native

SRC = src/*.cpp src/*.c
INC = -Iinclude

GL_LFLAGS = -lGL -lGLU -lglut

all: clean build-gl unshaded-gl flat-gl

ppm: clean build unshaded flat

build-gl:
	@echo "Building with OpenGL..."
	@$(CPP_RELEASE) $(INC) main.cpp $(SRC) -o main $(GL_LFLAGS) -DUSE_OPENGL

build:
	@echo "Building..."
	@$(CPP_RELEASE) $(INC) main.cpp $(SRC) -o main

unshaded:
	@echo "Rendering Part 1 (Unshaded)..."
	@./main --shading=NONE &
	@echo "Done"

unshaded-gl:
	@echo "Rendering Part 1 (Unshaded) with OpenGL..."
	@./main --shading=NONE &
	@echo "Done"


flat:
	@echo "Rendering Part 2 (Flat Shading)..."
	@./main --shading=FLAT &
	@echo "Done"

flat-gl:
	@echo "Rendering Part 1 (Flat Shading) with OpenGL..."
	@./main --shading=FLAT &
	@echo "Done"




clean:
	@rm -f main
