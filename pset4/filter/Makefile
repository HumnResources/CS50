CC=clang
OUTPUT=filter

g: filter
	./filter -g images/yard.bmp out.bmp
r: filter
	./filter -r images/tower.bmp out.bmp
e: filter
	./filter -e images/stadium.bmp out.bmp
b: filter
	./filter -b images/yard.bmp out.bmp

filter: filter.c
	$(CC) -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -lm -o $(OUTPUT) $(OUTPUT).c helpers.c

clean:
	rm filter out.bmp