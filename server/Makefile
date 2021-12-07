TARGET=server
CC=gcc

OBJS=server.o hangman.o request.o protocol.o

LD=gcc
LDLFLAGS=-lpthread

all: $(TARGET)

server: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDLFLAGS)

server.o: server.c hangman.c
	$(CC) -c server.c -o server.o

hangman.o: hangman.c
	$(CC) -c hangman.c -o hangman.o

request.o: ../request/request.c 
	$(CC) -c ../request/request.c -o request.o

protocol.o: ../request/protocol/protocol.c
	$(CC) -c ../request/protocol/protocol.c -o protocol.o
 
clean:
	rm -f *.o
