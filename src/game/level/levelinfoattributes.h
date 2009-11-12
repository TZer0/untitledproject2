// No header guards should be provided for this file
// The file describes the attributes for the cLevelInfo class
// ATTR(name, file, type, load) should be defined before including this file 

// FYI ATTR = Attribute

#ifndef ATTR
#error ATTR(name, file, type, load) macro should be defined
#endif

// 'NEXT' and '_END' is reserved
ATTR(name, 'NAME', std::string, string)
ATTR(sizex, 'SIZX', int, int)
ATTR(sizey, 'SIZY', int, int)
ATTR(mapfile, 'MAPF', std::string, string)


// etc..

#undef ATTR

