TARGET=client
CC=gcc
OBJS=client.o
LD=gcc

all: $(TARGET)

client: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS)

client.o: client.c
	$(CC) -c client.c -o client.o

clean:
	rm -f *.o
