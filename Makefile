# Project: hypjsch

GUI = hypjsch
CLI = hypjsch_cli
RM  = rm -f 

CPP = g++
CFLAGS =
LIBS := $(shell pkg-config --libs sdl2)
TESTLIBS = -lSDL2_test

all:	$(GUI) $(CLI)

clean:
	$(RM) $(GUI) $(CLI)

$(GUI): hypjsch.cpp
	${CPP} ${CFLAGS} keycodes.cpp hypjsch.cpp ${LIBS} ${TESTLIBS} -o ${GUI}

$(CLI): hypjsch_cli.cpp
	${CPP} ${CFLAGS} hypjsch_cli.cpp ${LIBS} -o ${CLI}

.PHONY: all clean
