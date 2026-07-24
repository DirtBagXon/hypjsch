# Project: hypjsch

GUI = hypjsch
CLI = hypjsch_cli
RM  = rm -f 

CPP = g++
CFLAGS := $(shell pkg-config --cflags sdl3)
LIBS := $(shell pkg-config --libs sdl3)

all:	$(GUI) $(CLI)

clean:
	$(RM) $(GUI) $(CLI)

$(GUI): hypjsch.cpp keycodes.cpp
	${CPP} ${CFLAGS} keycodes.cpp hypjsch.cpp ${LIBS} -o ${GUI}

$(CLI): hypjsch_cli.cpp
	${CPP} ${CFLAGS} hypjsch_cli.cpp ${LIBS} -o ${CLI}

.PHONY: all clean
