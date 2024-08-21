rwc: rwc.o
	gcc -g rwc.o -o bin/rwc
rwc.o: rwc.c 
	gcc -g -c rwc.c
run: rwc
	bin/rwc
clean:
	rm -f bin/rwc
	rm -f *.o

format: *.c
	gcc-format -style=Google -i *.c
