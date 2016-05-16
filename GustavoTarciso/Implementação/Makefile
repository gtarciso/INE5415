CC = g++
CFLAGS1 = -std=c++11 -Wall -c -Isrc/

RM = rm
TRASH = *.o

OBJ = main.o state.o automata.o

.PHONY: all
all: ${OBJ}
	${CC} -o main $?
	./main < tests/test_file2.in
	./main < tests/test_file3.in
	${RM} ${TRASH}

%.o: src/%.cpp
	${CC} ${CFLAGS1} -o $@ $<

.PHONY: clean
clean:
	${RM} ${TRASH}
