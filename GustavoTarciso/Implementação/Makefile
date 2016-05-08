CC = g++
CFLAGS1 = -std=c++11 -Wall -c -Isrc/

RM = rm
TRASH = *.o

OBJ = main.o state.o

.PHONY: all
all: ${OBJ}
	${CC} -o main $?
	${RM} ${TRASH}

%.o: src/%.cpp
	${CC} ${CFLAGS1} -o $@ $<

.PHONY: clean
clean:
	${RM} ${TRASH}
