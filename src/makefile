ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: mds

build: mds

install: mds
	install -d $(PREFIX)/bin
	install -m 777 mds $(PREFIX)/bin

mds: mds.c markdown.h
	gcc -g mds.c -o mds

markdown.h: markdown.peg
	peg -v markdown.peg > markdown.h

clean:
	rm markdown.h
	rm mds
