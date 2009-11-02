#ifndef LEVEL_H
#define LEVEL_H

#include "../misc/moduletemplate.h"
#include "levelinfo.h"
#include <map>
#include <string>

class cmLevel : public cDataSystem{
    private:
        std::map <std::string, cLevelInfo> levelInfo;
        cLevelInfo *currentLevel;

    public:
        void init();
        void level_init();      
        int load();
        void process(double delta);
        void draw();
        void clear_data();
};

#endif