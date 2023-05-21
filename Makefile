CFLAGS+= -g -Werror

ergotype: train.o homerows.o exercise.o skillset.o input.o output.o word.o line.o

clean:
	rm -f *.o
	rm -f ergotype ergotype.o

PHONY: clean
