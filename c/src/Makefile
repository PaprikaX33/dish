exec_name	= didsh
prefix		= /usr/local
exec_prefix	= $(prefix)
bindir		= $(exec_prefix)/bin

export prefix
export bindir
export exec_prefix

compile_name := $(exec_name)
cflags := -g -Og -Wall -Wextra -Wshadow -Wcast-align -Wunused -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2

all : idsh

idsh : $(compile_name)

$(compile_name) : main.o
	$(CC) $(cflags) -o $(compile_name) $^ -ldl

%.o : %.c
	$(CC) $(cflags) -c -o $@ $^

clean :
	-rm *.o $(compile_name)

check : all
	./$(compile_name)
	@echo "*** Test Passed ***"

install :
	install -d $(DESTDIR)$(bindir)
	install -m 0755 $(exec_name) $(DESTDIR)$(bindir)

uninstall :
	-rm $(DESTDIR)$(bindir)/$(exec_name)

.PHONY: all clean check install uninstall
