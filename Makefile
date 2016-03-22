CPP = g++ -std=c++11 -Wall -pedantic

CPP_DEBUG = @$(CPP) -g
CPP_RELEASE = @$(CPP) -O2 -march=native

SRC = src/*.cpp deps/arg-parser/argparser.c
INC = -Iinclude -Ideps -Ideps/arg-parser/

GL_LFLAGS = -lGL -lGLU -lglut

all: gl

ppm: build-ppm unshaded-ppm flat-ppm gouraud-ppm phong-ppm clean
gl: build-gl unshaded-gl flat-gl gouraud-gl phong-gl clean

# Compilation
build-gl:
	@echo "Building with OpenGL..."
	@$(CPP_RELEASE) $(INC) main.cpp $(SRC) -o main $(GL_LFLAGS) -DUSE_OPENGL
build-ppm:
	@echo "Building..."
	@$(CPP_RELEASE) $(INC) main.cpp $(SRC) -o main

# Part 1 (Unshaded)
unshaded-ppm:
	@echo "Rendering Part 1 (Unshaded)..."
	@./main --shading=NONE &
	@echo "Done"
unshaded-gl:
	@echo "Rendering Part 1 (Unshaded) with OpenGL..."
	@./main --shading=NONE &
	@echo "Done"

# Part 2 (Flat Shading)
flat-ppm:
	@echo "Rendering Part 2 (Flat Shading)..."
	@./main --shading=FLAT &
	@echo "Done"
flat-gl:
	@echo "Rendering Part 2 (Flat Shading) with OpenGL..."
	@./main --shading=FLAT &
	@echo "Done"

# Part 3 (Gouraud Shading)
gouraud-ppm:
	@echo "Rendering Part 3 (Gouraud Shading)..."
	@./main --shading=GOURAUD &
	@echo "Done"
gouraud-gl:
	@echo "Rendering Part 3 (Gouraud Shading) with OpenGL..."
	@./main --shading=GOURAUD &
	@echo "Done"

# Part 4 (Phong Shading)
phong-ppm:
	@echo "Rendering Part 4 (Phong Shading)..."
	@./main --shading=PHONG &
	@echo "Done"
phong-gl:
	@echo "Rendering Part 4 (Phong Shading) with OpenGL..."
	@./main --shading=PHONG &
	@echo "Done"

# Clean
clean:
	@rm -f main
