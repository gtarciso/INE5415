CC = g++
CFLAGS1 = -std=c++11 -Wall -Isrc/

INFILES:=$(shell find tests/*.in)
OUTFILES:=$(patsubst tests/%.in,results/%.out,$(INFILES))

RM = rm -f
TRASH = *.o results/*
OBJ = main.o state.o automata.o

.PHONY: all
all: eval

main: ${OBJ}
	${CC} -o main $?
	#./main < tests/test_file2.in > results/test_file2.out
	#./main < tests/test_file3.in > results/test_file3.out
	#./main < tests/test_file1.in # > results/test_file1.out
	${RM} ${TRASH}

%.o: src/%.cpp
	${CC} -c ${CFLAGS1} -o $@ $<

.PHONY: eval

results/%.out: tests/%.in | main
	./main <$< >$@	

eval: ${OUTFILES}
	echo "done!\n"

.PHONY: clean
clean:
	${RM} ${TRASH}
	rm -f main
	
.PHONY: main	

