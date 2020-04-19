all: md_shell

md_shell: md_shell.c markdown.h
	gcc -g md_shell.c -o md_shell

markdown.h: markdown.peg
	peg -v markdown.peg > markdown.h

clean:
	rm markdown.h
	rm md_shell

test: md_shell
	cat test.md | ./md_shell
