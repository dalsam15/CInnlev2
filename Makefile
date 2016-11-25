cc=gcc
cflags=-g -Wall 
cflags2= -lm

TARGET = main
all: $(TARGET)

$(TARGET): main.o thing.o
	$(cc) $(cflags) -o $(TARGET) $(cflags) main.o thing.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

thing.o:
	$(CC) $(CFLAGS) -c -o thing.o thing.c

clean:
	rm $(TARGET) *.o


memCheck:
	valgrind --tool=memcheck --leak-check=yes ./main wolf/


