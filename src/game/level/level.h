#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <string>
#include <vector>

#include "../misc/moduletemplate.h"
#include "levelinfo.h"

#include "../collision/collision.h"
#include "../collision/colapply.h"
#include "../collision/colmap.h"

#define MOD_LEVEL 42
#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 30

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
        std::map <std::string, cLevelInfo> levelInfo;
        cLevelInfo *currentLevel;
        std::vector<std::vector <int> > tiles;
        
        cCollision *rect;   // Rectangle collision instance
        cVector colpos;     // Position of collision instance
    public:
        cmLevel() : cApplyCollision(MOD_LEVEL, 4, LEVEL_WIDTH*32, LEVEL_HEIGHT*32)
            { }
        
        void init();
        void level_init();      
        int load();
        void process(double delta);
        void draw();
        void clear_data();
        virtual ~cmLevel() {}
        
        // Collision functions
        void collision_function(int caller_id, void*inst);
        bool test_collision(int dial_id, cCollision *target) {return false;}
};

#endif

