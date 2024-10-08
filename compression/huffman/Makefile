
compile_test: ../munit/munit.h ../munit/munit.c ./bit_writer.h ./bit_writer.c ./test_bit_writer.c
	gcc -o bin/test_bit_writer ../munit/munit.c ./bit_writer.c ./test_bit_writer.c


unit-test: compile_test
	bin/test_bit_writer
