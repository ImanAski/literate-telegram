V =

ifeq ($(strip $(V)),)
	E = @echo
	Q = @
else
	E = @\#
	Q =
endif
export E Q

PROGRAM = plotter


SRC=main.c point.c line.c circle.c repl.c utils.c token.c

OBJ=$(SRC:.c=.o)

HDR=enums.h funcs.h structs.h defs.h


CC = gcc
WARNINGS=-Wall -Wstrict-prototypes


LIBS=-lm

LFLAGS=-hbx

CFLAGS=-O2 $(WARNINGS) -g

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(E) "   LINK        " $@
	$(Q) $(CC) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

%.o: %.c $(HDR)

clean:
	$(E) "   CLEAN        "
	$(Q) rm -f $(PROGRAM) *.o


.PHONY: all clean
