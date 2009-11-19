#ifndef LEVEL_H
#define LEVEL_H

#include "../misc/moduletemplate.h"
#include "levelinfo.h"
#include "tile.h"
#include <map>
#include <string>
#include <vector>

#include "../misc/moduletemplate.h"
#include "levelinfo.h"
#include "../collision/collision.h"
#include "../collision/colapply.h"
#include "../collision/colmap.h"

#define MOD_LEVEL 42

struct sLevelCollision {
    // Short is short, saves us some memory.
    // Only downside is it limits level size to 65535
    unsigned short xi,yi;
    
    sColSectorInstance cols;
    sLevelCollision(unsigned short xi, unsigned short yi) : xi(xi), yi(yi), cols(this)
        { }
};

class cmLevel : public cDataSystem, public cApplyCollision {
    private:
        std::map <std::string, cLevelInfo*> levelInfo;
        cLevelInfo *curLev; // current level
        std::vector<std::vector <cTile> > tiles;
        
        cCollision *rect;   // Rectangle collision instance
        cVector colpos;     // Position of collision instance
    public:
        cmLevel() : cApplyCollision(MOD_LEVEL, 4, 70*32, 35*32)
            { }
        
        void init();
        void level_init();      
        int load();
        void process(double delta);
        void draw();
        void clear_data();

        int get_sizex() {return curLev->get_sizex();}
        int get_sizey() {return curLev->get_sizey();}

        virtual ~cmLevel() {}
        
        // Collision functions
        void collision_function(int caller_id, void*inst);
        bool test_collision(int dial_id, cCollision *target) {return false;}
};

#endif

