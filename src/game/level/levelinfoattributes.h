// No header guards should be provided for this file
// The file describes the attributes for the cLevelInfo class
// ATTR(name, type) should be defined before including this file 

// FYI ATTR = Attribute

#ifndef ATTR
#error ATTR(name, type) macro should be defined
#endif

ATTR(sizex, 'SIZX', int, int)
ATTR(sizey, 'SIZY', int, int)
ATTR(mapfile, 'MAPF', std::string, string)


// etc..

#undef ATTR

