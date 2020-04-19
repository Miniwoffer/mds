EXSAMPLE_MDS := $(wildcard *.mds)
EXSAMPLE_MD := $(patsubst %.mds,%.md, $(EXSAMPLE_MDS))

all: $(EXSAMPLE_MD)

%.md: %.mds ../src/mds
	../src/mds < $< >$@

clean:
	rm EXSAMPLE_MD
