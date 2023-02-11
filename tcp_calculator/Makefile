CC=/usr/bin/gcc
CFLAGS=-O2 -Wall

all: tcp_server tcp_client

tcp_server: tcp_server.c
	$(CC) $(CFLAGS) -o ./bin/tcp_server tcp_server.c

tcp_client: tcp_client.c
	$(CC) $(CFLAGS) -o ./bin/tcp_client tcp_client.c

clean: