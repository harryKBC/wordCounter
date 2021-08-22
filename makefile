CFLAGS = -ansi -Wall -pedantic
CC = gcc
OBJECTS = main.o array_list.o fileio.o helpers.o menu.o shared.o linked_list.o

main: ${OBJECTS}
	${CC} ${CFLAGS} -o cpt220_counter ${OBJECTS}

array_list.o: array_list.c array_list.h
	 ${CC} ${CFLAGS} -c array_list.c array_list.h

fileio.o: fileio.c fileio.h helpers.h
	 ${CC} ${CFLAGS} -c fileio.c fileio.h helpers.h

helpers.o:helpers.c helpers.h shared.h
	 ${CC} ${CFLAGS} -c helpers.c helpers.h shared.h

menu.o: menu.c menu.h fileio.h array_list.h helpers.h linked_list.h
	 ${CC} ${CFLAGS} -c menu.c menu.h fileio.h array_list.h helpers.h linked_list.h

shared.o: shared.c shared.h
	 ${CC} ${CFLAGS} -c shared.c shared.h

linked_list.o: linked_list.c linked_list.h array_list.h
	 ${CC} ${CFLAGS} -c linked_list.c linked_list.h array_list.h

clean:
	 rm -rf *.o *.gch
