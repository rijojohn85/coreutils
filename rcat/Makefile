rcat: rcat.o helpers.o
	gcc -g rcat.o helpers.o -o bin/rcat
rcat.o: rcat.c  ../helpers/helpers.h
	gcc -g -c rcat.c
helpers.o: ../helpers/helpers.c ../helpers/helpers.h
	gcc -g -c ../helpers/helpers.c
run: rcat
	bin/rcat
clean:
	rm -f bin/rcat
	rm -f *.o

format: *.c
	gcc-format -style=Google -i *.c
