all: build

run: build
	./a.out compareFiles.c main.c

build: a.out

a.out: main.c
	gcc main.c compareFiles.c

clean:
	rm a.out differencesOutput