all:
	gcc repl.c -o repl -W -Wall

clean:
	rm -rf repl