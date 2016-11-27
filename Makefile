cc=gcc
cflags=-g -Wall 
cflags2= -lm

TARGET = main
all: $(TARGET)

$(TARGET): main.o puzzleMaker.o
	$(cc) $(cflags) -o $(TARGET) $(cflags) main.o puzzleMaker.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

puzzleMaker.o:
	$(CC) $(CFLAGS) -c -o puzzleMaker.o puzzleMaker.c

clean:
	rm $(TARGET) *.o mickey_merged.txt wolf_merged.txt


memCheck:
	valgrind --tool=memcheck --leak-check=yes ./main wolf/


