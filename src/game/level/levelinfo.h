#ifndef LEVELINFO_H
#define LEVELINFO_H

#include <string>
#include <iostream>
#include <map>
#include "../misc/vector.h"
#include "../misc/file.h"
#include "../game.h"



class cLevelInfo{
    private:
        // generate attributes:
        #define ATTR(name, file, type, load) type name;
        #include "levelinfoattributes.h"

    public:
        // generate accessor functions:
        #define ATTR(name, file, type, load) type get_##name() {return name;}
        #include "levelinfoattributes.h"

        void clear_data();
        int  load(PACKFILE *fp);
};

#endif

