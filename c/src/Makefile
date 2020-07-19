exec_name	= didsh
prefix		= /usr/local
exec_prefix	= $(prefix)
bindir		= $(exec_prefix)/bin
version_mj	= 0
version_mn	= 1
version_pt	= 0

source_file	= main
header_file	=
includ_file	= verString.inc
csrc_file	= $(source_file:%=%.o)
object_file	= $(csrc_file:.c=.o)


export prefix
export bindir
export exec_prefix

compile_name := $(exec_name)
cflags := -std=c11 -g -Og -Wall -Wextra -Wshadow -Wcast-align -Wunused -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2
vrflag = -DVERSION_MAJOR=$(version_mj) -DVERSION_MINOR=$(version_mn) -DVERSION_PATCH=$(version_pt)

all : idsh

idsh : $(compile_name)

$(compile_name) : $(object_file)
	$(CC) $(cflags) -o $(compile_name) $(object_file) -ldl

main.o :  main.c $(includ_file) $(header_file)
	$(CC) $(cflags) $(vrflag) -c -o $@ $<

$(object_file) : %.o :  %.c
	$(CC) $(cflags) $(vrflag) -c -o $@ $<

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
