CC = gcc
CFLAGS = -Wall -Wextra

program: implemention.c
    $(CC) $(CFLAGS) -o implemention implemention.c

clean:
    rm -f implemention
