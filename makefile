all:
	mkdir -p bin && \
	gcc recl.c -o bin/c-recl -W -Wall -std=c99 -g

debug: all
	gdb bin/c-recl

clean:
	rm -rf bin

run: all
	bin/c-recl

install: all
	sudo cp bin/c-recl /usr/local/bin/