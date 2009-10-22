SOURCES = main.cpp ./game/init.cpp ./game/game.cpp ./game/draw.cpp ./game/misc/timer.cpp ./game/misc/input.cpp
CC = g++
CFLAGS = $(shell allegro-config --cflags) -Wall -pedantic
LDFLAGS = $(shell allegro-config --libs)

paddy : $(SOURCES)
	$(CC) $(SOURCES) $(OUTPUT_OPTION) $(CFLAGS) $(LDFLAGS)

clean :
	rm paddy
