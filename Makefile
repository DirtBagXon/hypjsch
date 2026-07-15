# Project: hypjsch

GUI = hypjsch
CLI = hypjsch_cli
RM  = rm -f 

CPP = g++
CFLAGS =
LIBS := $(shell pkg-config --libs sdl3)
TESTLIBS = -lSDL3_test

all:	$(GUI) $(CLI)

clean:
	$(RM) $(GUI) $(CLI)

$(GUI): hypjsch.cpp keycodes.cpp
	${CPP} ${CFLAGS} keycodes.cpp hypjsch.cpp ${TESTLIBS} ${LIBS} -o ${GUI}

$(CLI): hypjsch_cli.cpp
	${CPP} ${CFLAGS} hypjsch_cli.cpp ${LIBS} -o ${CLI}

.PHONY: all clean
