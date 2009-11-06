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
          game/enemy/enemy.cpp\
          game/misc/vector.cpp\
          game/weapon/weapon.cpp\
          game/level/level.cpp

CXX = g++
CFLAGZ = $(shell allegro-config --cflags) -Wall
LDFLAGZ = $(shell allegro-config --libs)
LIB = -Ilua-5.1.4/include/ -Llua-5.1.4/lib/ -llua

up2 : $(SOURCEZ)
	$(CXX) $(SOURCEZ) $(OUTPUT_OPTION) $(CFLAGZ) $(LDFLAGZ) $(LIB)
	mv up2 ../bin

clean :
	rm ../bin/up2

install:
	install -d $(INSTALL_PREFIX)/bin/
	$(LT) --mode=install install up2 $(INSTALL_PREIX)/bin/up2

uninstall:
	rm -f $(INSTALL_PREFIX)/bin/up2
