

all: renderer

renderer: renderer.cpp
	g++ -o renderer.exe renderer.cpp


clean:
	rm -rf *.o *.exe
