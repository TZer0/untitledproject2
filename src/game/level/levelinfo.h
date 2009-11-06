#ifndef LEVELINFO_H
#define LEVELINFO_H

#include <string>
#include <iostream>
#include "../misc/vector.h"

class cLevelInfo{
    private:
        std::string abc;

// generate attributes:
#define ATTR(name, type) type name;
#include "levelinfoattributes.h"

    public:
// generate accessor functions:
#define ATTR(name, type) type get_##name() {return name;}
#include "levelinfoattributes.h"

        void clear_data();
        int  load(std::istream f);
};

#endif

