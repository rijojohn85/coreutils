rcat: rcat.c
	gcc-14 rcat.c -o bin/rcat
run: rcat
	bin/rcat
clean:
	rm -f bin/rcat

format: *.c
	clang-format -style=Google -i *.c
