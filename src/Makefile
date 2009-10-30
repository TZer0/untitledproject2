SOURCES = main.cpp ./game/init.cpp ./game/game.cpp ./game/draw.cpp ./game/misc/timer.cpp ./game/misc/input.cpp ./game/misc/file.cpp ./game/misc/log.cpp ./game/player/player.cpp
CC = g++
CFLAGS = $(shell allegro-config --cflags) -Wall -g3
LDFLAGS = $(shell allegro-config --libs)

paddy : $(SOURCES)
	$(CC) $(SOURCES) $(OUTPUT_OPTION) $(CFLAGS) $(LDFLAGS)

clean :
	rm paddy
