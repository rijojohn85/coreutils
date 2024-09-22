compress: compress.c
	gcc compress.c -o bin/compress
run: compress
	bin/compress
clean:
	rm -rf bin/compress
test:
	bundle exec rspec
format: *.c
	clang-format -style=Google -i *.c
