CFLAGS = -O2 -std=gnu11 -pedantic -Wall -lm -lpthread -lrt

all: ShellZ

ShellZ: src/*.c
	mkdir -p build
	gcc $(CFLAGS) -o build/ShellZ src/*.c

clean:
	rm -rf build/
