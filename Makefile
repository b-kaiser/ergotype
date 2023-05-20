CFLAGS+= -g

ergotype: homerows.o exercise.o

clean:
	rm -f *.o
	rm -f ergotype ergotype.o

PHONY: clean
