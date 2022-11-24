CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 #cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,%(PROGS)) step1.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o step1.o
	g++ -o $@ $^
%.o: %.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

step1.o: step1.hpp
