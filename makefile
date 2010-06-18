all:
	gcc repl.c -o repl -W -Wall -std=c99

clean:
	rm -rf repl