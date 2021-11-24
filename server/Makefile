TARGET=server
CC=gcc

OBJS=server.o hangman.o

LD=gcc
LDLFLAGS=-lpthread

all: $(TARGET)

server: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDLFLAGS)

server.o: server.c hangman.c
	$(CC) -c server.c -o server.o

hangman.o: hangman.c
	$(CC) -c hangman.c -o hangman.o

clean:
	rm -f *.o
