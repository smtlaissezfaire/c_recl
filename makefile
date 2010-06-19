all:
	mkdir -p bin && \
	gcc repl.c -o bin/repl -W -Wall -std=c99 -g

debug: all
	gdb bin/repl

clean:
	rm -rf bin

run: all
	bin/repl
