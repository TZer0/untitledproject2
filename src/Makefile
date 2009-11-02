SOURCEZ = main.cpp\
          game/init.cpp\
          game/game.cpp\
          game/draw.cpp\
          game/misc/timer.cpp\
          game/misc/input.cpp\
          game/misc/file.cpp\
          game/misc/log.cpp\
          game/player/player.cpp\
          game/misc/animation/anim.cpp\
          game/misc/animation/animproc.cpp\
          game/misc/loadimage.cpp\
          game/misc/animation/luaanimation.cpp\
          game/misc/animation/loadanimation.cpp\
          game/load.cpp\

# Missing? :
#game/enemy/enemy.cpp
#game/misc/vector.cpp
#game/weapon/weapon.cpp
#game/level/level.cpp

CC = g++
CFLAGZ = $(shell allegro-config --cflags) -Wall
LDFLAGZ = $(shell allegro-config --libs)
LIB = -Ilua-5.1.4/include/ -Llua-5.1.4/lib/ -llua

up2 : $(SOURCEZ)
	$(CC) $(SOURCEZ) $(OUTPUT_OPTION) $(CFLAGZ) $(LDFLAGZ) $(LIB)
	mv up2 ../bin

clean :
	rm ../bin/up2

install:
	cp ../bin/up2 /usr/local/bin/up2

uninstall:
	rm /usr/local/bin/up2
