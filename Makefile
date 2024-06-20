CC= gcc
CFLAGS = -Wall -Wextra -pedantic

maxfile: maxfile.c
	$(CC) $(CFLAGS) -o maxfile maxfile.c

clean:
	rm -f maxfile
