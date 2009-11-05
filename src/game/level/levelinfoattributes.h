// No header guards should be provided for this file
// The file describes the attributes for the cLevelInfo class
// ATTR(name, type) should be defined before including this file 

#ifndef ATTR
#error ATTR(name, type) macro should be defined
#endif

ATTR(sizex, int)
ATTR(sizey, int)
ATTR(mapfile, std::string)

// etc..

#undef ATTR
