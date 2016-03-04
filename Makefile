CPP = g++ -std=c++11 -Wall -pedantic

CPP_DEBUG = @$(CPP) -g
CPP_RELEASE = @$(CPP) -O2 -march=native

SRC = src/*.cpp
INC = -Iinclude

GL_LFLAGS = -lGL -lGLU -lglut

all: part1-gl clean

part1:
	@echo "Part 1"
	@echo "Building..."
	@$(CPP_RELEASE) $(INC) part1.cpp $(SRC) -o part1
	@echo "Rendering..."
	@./part1
	@echo "Done"

part1-gl:
	@echo "Part 1 using OpenGL"
	@echo "Building..."
	@$(CPP_RELEASE) $(INC) part1.cpp $(SRC) -o part1 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Rendering..."
	@./part1
	@echo "Done"

clean:
	@rm -f part1
