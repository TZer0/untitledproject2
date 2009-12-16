SOURCEZ = main.cpp\
		game/init.cpp\
		game/game.cpp\
		game/draw.cpp\
        game/load.cpp\
		game/animation/anim.cpp\
		game/animation/animproc.cpp\
		game/animation/luaanimation.cpp\
		game/animation/loadanimation.cpp\
		game/bullet/bullet.cpp\
		game/collision/colapply.cpp\
		game/collision/collision.cpp\
		game/collision/colmap.cpp\
		game/collision/sat.cpp\
		game/enemy/enemy.cpp\
		game/level/level.cpp\
        game/level/levelinfo.cpp\
        game/level/tile.cpp\
		game/misc/timer.cpp\
		game/misc/input.cpp\
		game/misc/file.cpp\
		game/misc/log.cpp\
		game/misc/loadimage.cpp\
        game/misc/luautil.cpp\
		game/misc/vector.cpp\
		game/player/player.cpp\
		game/weapon/weapon.cpp\
		game/weapon/luaweapon.cpp\


OBJECTZ = $(SOURCEZ:.cpp=.o)
# GNU
# CFLAGZ = $(shell allegro-config --cflags) -c -Wall -I/usr/include/lua5.1
# LDFLAGZ = $(shell allegro-config --libs)
# LIB = -Ilua-5.1.4/include/ -Llua-5.1.4/lib/ -llua5.1

# BSD
CFLAGZ = -I/usr/local/include -c -Wall -I/usr/include/lua5.1
LDFLAGZ = -L/usr/local/lib -L/usr/X11R6/lib -Wl,--export-dynamic -lalleg -lalleg_unsharable
LIB = -Ilua-5.1.4/include/ -Llua-5.1.4/lib/ -llua

all: $(SOURCEZ) up2

up2: $(OBJECTZ)
	$(CXX) $(LDFLAGZ) $(LIB) $(OBJECTZ) -o $@
	mv up2 ../bin

.cpp.o:
	$(CXX) $(CFLAGZ) $< -o $@


clean:
	rm -f $(OBJECTZ)

install:
	install -d $(INSTALL_PREFIX)/bin/
	$(LT) --mode=install install ../bin/up2 $(INSTALL_PREIX)/bin/up2

uninstall:
	rm -f $(INSTALL_PREFIX)/bin/up2

test: all
	../bin/up2
