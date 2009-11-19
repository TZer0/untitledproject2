// No header guards should be provided for this file
// The file describes the attributes for the cLevelInfo class
// ATTR(name, file, type, load) should be defined before including this file 

// FYI ATTR = Attribute

#ifndef ATTR
#error ATTR(name, file, type, load) macro should be defined
#endif

#ifndef FOURCC
#define FOURCC(a, b, c, d) (a | b << 8 | c << 16 | d << 24)
#endif

// 'NEXT' and '_END' is reserved
ATTR(name, FOURCC('N','A','M','E'), std::string, string)
ATTR(sizex, FOURCC('S','I','Z','X'), int, int)
ATTR(sizey, FOURCC('S','I','Z','Y'), int, int)
ATTR(mapfile, FOURCC('M','A','P','F'), std::string, string)


// etc..

#undef ATTR

