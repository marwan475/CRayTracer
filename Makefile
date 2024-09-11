

all: renderer 

renderer: render vector
	g++ -o renderer.exe renderer.o vector3.o

render: renderer.cpp
	g++ -o renderer.o -c renderer.cpp 

vector: vec3.h vec3functions.cpp
	g++ -o vector3.o -c vec3functions.cpp

clean:
	rm -rf *.o *.exe
