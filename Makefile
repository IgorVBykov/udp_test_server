CC = gcc

CFLAGS = -c -Wall -std=c99

all: udp_test_server

udp_test_server: main.o
	$(CC) main.o $(LDFLAGS) -o udp_test_server

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *o udp_test_server

