rcat: rcat.o helpers.o
	clang -g rcat.o helpers.o -o bin/rcat
rcat.o: rcat.c  ../helpers/helpers.h
	clang -g -c rcat.c
helpers.o: ../helpers/helpers.c ../helpers/helpers.h
	clang -g -c ../helpers/helpers.c
run: rcat
	bin/rcat
clean:
	rm -f bin/rcat

format: *.c
	clang-format -style=Google -i *.c
