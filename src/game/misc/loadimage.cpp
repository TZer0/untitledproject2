/**
 * File: loadimage.cpp
 *
 * Description:	Handles loading of images.
 *              Loads all images on demand.
 *
 * (c)2009, by Raymond Loeberg
 */
// Loading includes
#include "loadimage.h"
#include "log.h"

// Other includes
#include "../game.h"

class cmImagesData mImagesData;

/**
 * Retrieves an image from the database, loading it if not already there.
 * @returns The image, or NULL on error.
 */
BITMAP *cmImagesData::retrieve(const char *file) {
	BITMAP *tmp;
	std::string fullname;
	std::map<std::string,BITMAP*>::iterator bmp;
	
	// Load the image if it isn't already loaded
	if((bmp=images.find(file)) == images.end()) {
		fullname = mGame->mFile->get_filename("images", file);
		tmp = load_bitmap(fullname.c_str(), NULL);
		LOGS(LDEBUG, "Loaded bitmap %p from %s", tmp, fullname.c_str());
		if(tmp==NULL) {
			return NULL;
		}
		images[std::string(file)] = tmp;
		return tmp;
	}
	
	// Return bitmap (from above in images.find())
	return bmp->second;
}

/**
 * Checks if a specific image is loaded
 * @returns 1 if loaded, else 0
 */
int cmImagesData::exists(const char *file) {
	return(images.find(file)!=images.end());
}
