TARGET = app

CC = gcc
CFLAGS = -std=c11


$(TARGET): main.o ui.o fileIO.o transmitter.o stack.o utils.o
	$(CC) main.o ui.o fileIO.o transmitter.o stack.o utils.o -o $(TARGET)

main.o: main.c ui.h
	$(CC) $(CFLAGS) -c main.c

ui.o: ui.c ui.h fileIO.h
	$(CC) $(CFLAGS) -c ui.c

fileIO.o: fileIO.c fileIO.h transmitter.h
	$(CC) $(CFLAGS) -c fileIO.c

transmitter.o: transmitter.c transmitter.h stack.h
	$(CC) $(CFLAGS) -c transmitter.c

stack.o: stack.c stack.h utils.h
	$(CC) $(CFLAGS) -c stack.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET)