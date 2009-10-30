SOURCEZ = main.cpp game/init.cpp game/game.cpp game/draw.cpp game/misc/timer.cpp game/misc/input.cpp game/misc/file.cpp game/misc/log.cpp game/player/player.cpp
CC = g++
CFLAGZ = $(shell allegro-config --cflags) -Wall -g3
LDFLAGZ = $(shell allegro-config --libs)

paddy : $(SOURCEZ)
	$(CC) $(SOURCEZ) $(OUTPUT_OPTION) $(CFLAGZ) $(LDFLAGZ)

clean :
	rm paddy
