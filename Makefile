V =

ifeq ($(strip $(V)),)
	E = @echo
	Q = @
else
	E = @\#
	Q =
endif
export E Q

BUILDDIR=build
TESTDIR=tests

PROGRAM = build/plotter
TEST_PROGRAM = build/tests/test_runner

SRC=main.c point.c line.c circle.c repl.c utils.c token.c globals.c parser.c nparse.c
OBJ=$(SRC:%.c=build/%.o)
HDR=enums.h funcs.h structs.h defs.h

TEST_SRC=tests/test_token.c tests/test_point.c unity/src/unity.c globals.c utils.c
TEST_OBJ=$(TEST_SRC:%.c=build/%.o)
TEST_DEPS=build/token.o build/point.o

CC = gcc
WARNINGS=-Wall -Wstrict-prototypes
LIBS=-lm
LFLAGS=-hbx
CFLAGS=-O2 $(WARNINGS) -g
TEST_CFLAGS=$(CFLAGS) -I tests/unity

all: $(PROGRAM)

test: $(TEST_PROGRAM)
	$(E) "   RUN TESTS   " $@
	$(Q) ./$(TEST_PROGRAM)

run: $(PROGRAM)
	$(E) "   RUN         " $@
	$(Q) ./$(PROGRAM)

$(PROGRAM): $(OBJ)
	$(E) "   LINK        " $@
	$(Q) mkdir -p $(@D)
	$(Q) $(CC) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

build/%.o: %.c $(HDR)
	$(E) "   CC          " $@
	$(Q) mkdir -p $(@D)
	$(Q) $(CC) $(CFLAGS) -c -o $@ $<

$(TEST_PROGRAM): $(TEST_OBJ) $(TEST_DEPS)
	$(E) "   LINK TEST   " $@
	$(Q) mkdir -p $(@D)
	$(Q) $(CC) $(LDFLAGS) -o $@ $(TEST_OBJ) $(TEST_DEPS) $(LIBS)

build/tests/%.o: tests/%.c $(HDR)
	$(E) "   CC TEST     " $@
	$(Q) mkdir -p $(@D)
	$(Q) $(CC) $(TEST_CFLAGS) -c -o $@ $<

build/tests/unity/%.o: tests/unity/%.c
	$(E) "   CC UNITY    " $@
	$(Q) mkdir -p $(@D)
	$(Q) $(CC) $(TEST_CFLAGS) -c -o $@ $<

clean:
	$(E) "   CLEAN        "
	$(Q) rm -rf build *.o


.PHONY: all run test clean
