CFLAGS+= -g -Werror -Wall -Wextra

LOCAL_LIBS_PATH = $(shell echo $$HOME)/.local

ifndef LOCAL_NCURSES
LDFLAGS += -lncurses
else
ergotype: .use_local_ncurses
CFLAGS += -I$(shell echo $$HOME)/.local/include
CFLAGS += -I$(shell echo $$HOME)/.local/include/ncurses
LDFLAGS += -L$(shell echo $$HOME)/.local/lib
LDLIBS += -lncurses
.use_local_ncurses:
	git submodule update --init
	cd ncurses; ./configure --prefix=$(LOCAL_LIBS_PATH) && make && make install
	touch $@
endif

ergotype: train.o homerows.o exercise.o skillset.o input.o output.o word.o line.o 

clean:
	rm -f *.o
	rm -f ergotype ergotype.o

PHONY: clean


