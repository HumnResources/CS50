CC=clang
OUTPUT=inheritance
SRC=inheritance.c

debug: inheritance
	debug50 ./$(OUTPUT)

test: inheritance
	./$(OUTPUT)

inheritance: $(SRC)
	$(CC) -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -lm -o $(OUTPUT) $(OUTPUT).c

clean:
	rm ./$(OUTPUT)