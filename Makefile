all: g++
	@echo "Done."

g++: src/*.cpp
	g++ -o trabalhocg src/main.cpp src/objects/*.cpp src/model/*.cpp src/services/*.cpp src/tinyxml/*.cpp  -lGL -lGLU -lglut

clean:
	@rm -f *.o trabalhocg
