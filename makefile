all: README.md

README.md: README.mds src/mds
	./src/mds < README.mds > README.md

install:
	make install -C src
