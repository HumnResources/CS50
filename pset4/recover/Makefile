CC=clang
OUTPUT=recover
SRC=recover.c

debug: recover
	debug50 ./$(OUTPUT)

test: recover
	./$(OUTPUT) card.raw

recover: $(SRC)
	$(CC) -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -lm -o $(OUTPUT) $(OUTPUT).c

clean:
	rm ./$(OUTPUT)
	rm -f *.jpg