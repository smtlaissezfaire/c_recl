all:
	mkdir -p bin && \
	gcc repl.c -o bin/repl -W -Wall -std=c99

clean:
	rm -rf bin