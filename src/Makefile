all: g++
	@echo "Done."

g++: *.cpp
	g++ -o out main.cpp input/*.cpp objects/*.cpp polygons/*.cpp services/*.cpp tinyxml/*.cpp  -lGL -lGLU -lglut

clean:
	@rm -f *.o out