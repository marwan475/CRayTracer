

all: renderer 

renderer: render vector
	g++ -o renderer.exe renderer.o vector3.o -g

render: renderer.cpp
	g++ -o renderer.o -c renderer.cpp -g

vector: vec3.h vec3functions.cpp
	g++ -o vector3.o -c vec3functions.cpp -g

clean:
	rm -rf *.o *.exe
