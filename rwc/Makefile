rwc: rwc.o helpers.o
	# gcc -g rwc.o -o bin/rwc 
	gcc-14 -g rwc.o helpers.o -o bin/rwc -largp -L /usr/local/Cellar/argp-standalone/1.3/lib/ -I /usr/local/Cellar/argp-standalone/1.3/include/ 
rwc.o: rwc.c ../helpers/helpers.h
	gcc-14 -g -c rwc.c -largp -L /usr/local/Cellar/argp-standalone/1.3/lib/ -I /usr/local/Cellar/argp-standalone/1.3/include/ 
	# gcc -g -c rwc.c 
helpers.o: ../helpers/helpers.c ../helpers/helpers.h
	gcc-14 -g -c ../helpers/helpers.c
run: rwc
	bin/rwc
clean:
	rm -f bin/rwc
	rm -f *.o

format: *.c
	gcc-format -style=Google -i *.c
