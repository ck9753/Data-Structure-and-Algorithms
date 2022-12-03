CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 #cyoa-step4
OBJS=$(patsubst %,%.o,%(PROGS)) page.o storyBook.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o page.o storyBook.o
	g++ -o $@ $^
%.o: %.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

page.o: page.hpp
storyBook.o: storyBook.hpp 
