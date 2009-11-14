#include "levelinfo.h"

using namespace std;

inline int read_int(PACKFILE *fp);
string read_string(PACKFILE *fp);

int cLevelInfo::load(PACKFILE *fp){

    while (!pack_feof(fp)){

        int type = read_int(fp);

        switch (type){
            // Generates a switch
            #define ATTR(name, file, type, load) case file: name = read_##load (fp); break;
            #include "levelinfoattributes.h"
            default: break;
        }
    }
    return 0;
}

int read_int(PACKFILE *fp){
    return pack_igetl(fp);
}

string read_string(PACKFILE *fp){
    return mGame->mFile->read_string(fp);
}