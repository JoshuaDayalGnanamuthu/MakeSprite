CFLAGS = -std=c99 -Wall -Wextra -pedantic -g
GCC = gcc

sprite: sprites.c
	$(GCC) $(CFLAGS) sprites.c -o sprite

clean:
	rm -f *.o sprite
