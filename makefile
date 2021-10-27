MYFLAGS=-c -Wall -g
OUT_EXEC=contactlist.out

all: prog.o datetime.o
	gcc prog.o datetime.o -o $(OUT_EXEC)

prog.o: prog.c 
	gcc prog.c -o prog.o $(MYFLAGS)

	

	
datetime.o: datetime.c
	gcc datetime.c -o datetime.o $(MYFLAGS)

delete: 
	rm *.o
	rm *.out
	

