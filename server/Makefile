TARGET=server
CC=gcc
INC_DIR=../
CFLAGS=-I$(INC_DIR)
OBJS=server.o hangman.o request.o protocol.o util.o

LD=gcc
LDLFLAGS=-lpthread

all: $(TARGET)

server: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDLFLAGS)

server.o: server.c hangman.c
	$(CC) -c server.c -o server.o $(CFLAGS)

util.o: ../util.c
	$(CC) -c ../util.c -o util.o $(CFLAGS)

hangman.o: hangman.c ../util.c
	$(CC) -c hangman.c -o hangman.o $(CFLAGS)

request.o: ../request/request.c 
	$(CC) -c ../request/request.c -o request.o $(CFLAGS)

protocol.o: ../request/protocol/protocol.c
	$(CC) -c ../request/protocol/protocol.c -o protocol.o $(CFLAGS)
 
clean:
	rm -f *.o
