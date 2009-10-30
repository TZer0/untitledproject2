/**
 * File: loadimage.h
 *
 * Description:	Header for image loading.
 *              Contains a class that handles loading and storage of images
 *
 * (c)2009, by Raymond Loeberg
 */
#ifndef IMAGES_LOADER_H
#define IMAGES_LOADER_H
// Global includes
#include <map>
#include <string>
#include <allegro.h>

// Other includes
#include "../misc/file.h"

/// Class that contains all loaded images
class cmImagesData {
	public:
		std::map<std::string,BITMAP *> images;
		BITMAP *retrieve(const char *);
		int exists(const char *);
};

extern class cmImagesData mImagesData;

#endif
