TARGET=client
CC=gcc
INC_DIR=../request
CFLAGS= -I$(INC_DIR)

OBJS=client.o request.o protocol.o

LD=gcc

all: $(TARGET)

client: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS)

client.o: client.c
	$(CC) -c client.c -o client.o $(CFLAGS)

request.o: ../request/request.c
	$(CC) -c ../request/request.c -o request.o

protocol.o: ../request/protocol/protocol.c
	$(CC) -c ../request/protocol/protocol.c -o protocol.o

clean:
	rm -f *.o
