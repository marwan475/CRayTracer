

all: renderer vector

renderer: renderer.cpp
	g++ -o renderer.exe renderer.cpp

vector: vec3.h vec3functions.cpp
	g++ -o vector3.o -c vec3functions.cpp

clean:
	rm -rf *.o *.exe
