# Compiler options
CC = gcc
CROSS_COMPILE - aarch64-none-linux-gnu
CFLAGS = -Wall _Wextra
LDFLAGS=

writer: writer.c
	$(CC) writer.c -o writer

CROSS_COMPILE: writer.c
	$(CROSS_COMPILE)-$(CC) writer.c writer-cc
clean:
	rm -rf writer writer-cc *.o

