CPP = g++ -std=c++11 -Wall -pedantic

CPP_DEBUG = @$(CPP) -g
CPP_RELEASE = @$(CPP) -O2 -march=native

SRC = src/*.cpp
INC = -Iinclude

GL_LFLAGS = -lGL -lGLU -lglut

all: unshaded-gl flat-gl

unshaded:
	@echo "Part 1 (Unshaded)"
	@echo "Building..."
	@$(CPP_DEBUG) $(INC) main.cpp $(SRC) -o main -DUNSHADED
	@echo "Rendering..."
	@./main &
	@echo "Done"

unshaded-gl:
	@echo "Part 1 (Unshaded) using OpenGL"
	@echo "Building..."
	@$(CPP_DEBUG) $(INC) main.cpp $(SRC) -o main $(GL_LFLAGS) -DUNSHADED -DUSE_OPENGL
	@echo "Rendering..."
	@./main &
	@echo "Done"

flat:
	@echo "Part 2 (Flat shading)"
	@echo "Building..."
	@$(CPP_DEBUG) $(INC) main.cpp $(SRC) -o main -DFLAT_SHADING
	@echo "Rendering..."
	@./main &
	@echo "Done"

flat-gl:
	@echo "Part 2 (Flat shading) using OpenGL"
	@echo "Building..."
	@$(CPP_DEBUG) $(INC) main.cpp $(SRC) -o main $(GL_LFLAGS) -DFLAT_SHADING -DUSE_OPENGL
	@echo "Rendering..."
	@./main &
	@echo "Done"

clean:
	@rm -f main
