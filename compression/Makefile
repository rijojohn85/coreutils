compress: compress.c
	gcc compress.c -o bin/compress
compile_test: test.o compress.o munit.o
	gcc -g test.o compress.o -o bin/compress_test
test.o: test.c compress.h
	gcc -g -c test.c
compress.o: compress.c compress.h
	gcc -g -c compress.c
munit.o: ./munit/munit.c ./munit/munit.h
	gcc -g -c ./munit/munit.c
run: compress
	bin/compress
clean:
	rm -rf bin/compress
test:
	bundle exec rspec
unit-test: compile_test
	bin/compress_test
format: *.c
	clang-format -style=Google -i *.c
