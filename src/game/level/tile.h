#ifndef TILE_H
#define TILE_H

#ifndef UINT
#define MY_TEMP_UINT_DEFINED
#define UINT unsigned int
#endif

class cTile{
    public:
        /* number after colon shows number of bits used */
        UINT tile        : 8;
        UINT ladder      : 1;
        UINT slippery    : 5;
        UINT kill        : 2;
        UINT invisible   : 1;
        UINT destroyable : 1;
        UINT water       : 1;
        UINT sink        : 1;
        UINT scriptdef   : 4;
        UINT unknown     : 8;

        // costructors:
        cTile() { cTile(0); }
        cTile(int iTile);

        // called before saving tile:
        int to_int();

        // operators:
        bool operator==(int test) {return tile == test;}
        bool operator!=(int test) {return tile != test;}
};
        
#ifdef MY_TEMP_UINT_DEFINED
#undef MY_TEMP_UINT_DEFINED
#undef UINT
#endif /* UINT */

#endif /* TILE_H */