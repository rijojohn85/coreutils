rcat: rcat.o helpers.o
	gcc-14 rcat.o helpers.o -o bin/rcat
rcat.o: rcat.c  ../helpers/helpers.h
	gcc-14 -c rcat.c
helpers.o: ../helpers/helpers.c ../helpers/helpers.h
	gcc-14 -c ../helpers/helpers.c
run: rcat
	bin/rcat
clean:
	rm -f bin/rcat

format: *.c
	clang-format -style=Google -i *.c
