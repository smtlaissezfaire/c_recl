all:
	mkdir -p bin && \
	gcc recl.c -o bin/recl -W -Wall -std=c99 -g

debug: all
	gdb bin/recl

clean:
	rm -rf bin

run: all
	bin/recl

install: all
	sudo cp bin/recl /usr/local/bin/c_recl