CC = gcc
CFLAGS = -Wall

TARGET = program

OBJS = main.o A.o B.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

A.o: A.c
	$(CC) $(CFLAGS) -c A.c

B.o: B.c
	$(CC) $(CFLAGS) -c B.c

clean:
	rm -f *.o $(TARGET)
