

all: renderer

renderer: renderer.c
	g++ -o renderer.exe renderer.c


clean:
	rm -rf *.o *.exe
