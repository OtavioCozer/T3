all: g++
	@echo "Done."

g++: *.cpp
	g++ -o out *.cpp -lGL -lGLU -lglut

clean:
	@rm -f *.o out