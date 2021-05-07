all: g++
	@echo "Done."

g++: *.cpp
	g++ -o trabalhocg main.cpp input/*.cpp objects/*.cpp model/*.cpp  services/*.cpp tinyxml/*.cpp  -lGL -lGLU -lglut

clean:
	@rm -f *.o trabalhocg