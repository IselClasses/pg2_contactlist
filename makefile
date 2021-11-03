MYFLAGS=-g -Wall -c
EXECUTABLENAME=contactsapp.out
LIBNAME=libcontacts.a
LIBMODULES=contacts.o datetime.o
MODULES=prog.o consolehelpers.o $(LIBNAME)

all: $(MODULES)
	gcc $(MODULES) -o $(EXECUTABLENAME) 
	
*.o: *.c
	gcc $(MYFLAGS) *.c
	
libcontacts.a: removeLib $(LIBMODULES)
	ar -vq $(LIBNAME) $(LIBMODULES)

run: all
	$(EXECUTABLENAME)
	
debug: all	
	insight $(EXECUTABLENAME)

removeLib:
	-rm *.a

clean:
	-rm *.o
	-rm *.out
	-rm *.a

