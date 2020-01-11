
CC=gcc
CFLAGS =Wall -Werror -std=c99 -o
FILES = main.c Database.c LinkedList.c Relation.c
EXECUTABLE = RDB

make : $(FILES)
	$(CC) -$(CFLAGS) $(EXECUTABLE) $(FILES)

run :
	./$(EXECUTABLE)

all : $(FILES)
	$(CC) -$(CFLAGS) $(EXECUTABLE) $(FILES)
	./$(EXECUTABLE)

clean :
	rm $(EXECUTABLE)

run-clean : $(FILES)
	$(CC) -$(CFLAGS) $(EXECUTABLE) $(FILES)
	./$(EXECUTABLE)
	rm $(EXECUTABLE)
