/**
 * File: colmap.cpp
 *
 * Description: Functions for a collision map system.
 *
 * (c)2009, by Raymond Loeberg
 */
// Other includes
#include "../misc/vector.h"
#include "colmap.h"
#include "colapply.h"

/**
 * Creates a collision map.
 * A quadtree with divisions from 2x2 to 2^depth x 2^depth is created.
 * \p w and \p h are the dimensions (in real-game units) of the map.
 *
 * @param depth The size of the bottom layer, as 2^depth x 2^depth.
 */
cColMap::cColMap(int depth, double w, double h)
{
	int res;
	cLayer *l;
	
	// Allocate memory for layers
	layers = new cLayer[depth];
	
	// Loop though all depths and assign data
	res = 2;  // Start at an initial size of 2x2
	for(int i=0; i<depth; i++,res*=2) {
		// The depth is doubled every iteration
		
		// Short hand for the layer
		l = &layers[i];
		
		// Allocate memory for rows
		l->md.reserve(res);     // Bitmap
		
		if(i==depth-1)
            l->data.reserve(res);   // Sector data: Only for bottom layer
		
		// For each row in layer
		for(int j=0;j<res;j++) {
		    // Allocate bitfield
		    std::vector<bool> v;
		    v.reserve(res);
			l->md[j] = v;
			
			// Data field, only for bottom layer
			if(i==depth-1) {
                std::vector<std::vector<sColSectorInstance*>*> dt;
                dt.reserve(res);
                
                l->data[j] = dt; // Add data vector
                
                // Create vector lists for instances that intersect with a sector
                for(int k=0;k<res;k++) {
                    std::vector<sColSectorInstance*> *zdata;
                    
                    zdata = new std::vector<sColSectorInstance*>;
                    /// @note Could possibly reserve a few elements to each sector when creating,
                    /// but left out for now.
                    l->data[j][k] = zdata;
                }
			}
		}
		
		// Set size of layer
		l->xw = w/double(res);
		l->yw = h/double(res);
		l->xys = res;
	}

	// Save the number of layers
	lc = depth;
}

void cColMap::resize(double w,double h)
{
    // Clear out old data
    clear();
    
    // Resize all layers
    for(int l=0; l<lc; l++) {
        cLayer *lay = &layers[l];
        
        lay->xw = w/double(lay->xys);
        lay->yw = h/double(lay->xys);
    }
}


/**
 * Returns the data at a given position in the collision map
 * Checking the smallest layer (due to infinitely small point test)
 */
std::vector<sColSectorInstance*> *cColMap::checkpoint(cVector pt)
{
	// Convert point
	int xi,yi;
	
	xi = layers[lc-1].getxi(pt.x);
	yi = layers[lc-1].getyi(pt.y);
	
	// Check out-of-bounds
	if(xi<0 || xi >= layers[lc-1].xys) return NULL;
	if(yi<0 || yi >= layers[lc-1].xys) return NULL;
	
	// Return data
	return(layers[lc-1].data[yi][xi]);
}

/**
 * Uses cApplyCollision to traverse the collision instance list for each touching sector
 *
 * @todo This function is sort of "backhacked" together, so it could use a cleanup.
 */
void cColMap::checkbox(cVector tl, cVector br, cApplyCollision *apc)
{
    cLayer *lay;
    int xl,xr;
    int yt,yb;
    // For each layer, starting at the top
    for(int i=0;i<lc;i++) {
        lay = &layers[i];
        
        // Get the indexes of the box
        // And make sure they're capped
        yt = lay->cap(  lay->getyi(tl.y)-1  );
        xl = lay->cap(  lay->getxi(tl.x)-1  );
        yb = lay->cap(  lay->getyi(br.y)+1  );
        xr = lay->cap(  lay->getxi(br.x)+1  );
        
        // Iterate through the box
        bool isCol = false;
        for(int iy=yt; iy<yb; iy++) {
            for(int ix=xl; ix<xr; ix++) {
                // If the bitmap says there is a collision in this sector
                if(lay->md[iy][ix]) {
                    // If we haven't reached the last layer
                    // we will flag that there is still more to go
                    if(i<lc-1) {
                        isCol = true;
                        goto next_layer;
                    }else {
                        // Calls the collision function for all colliding sectors
                        apc->iterate_collision(lay->data[iy][ix]);
                    }
                }
            }
        }

        // Clear everything at the last layer
        if(isCol) { // This should always be true, the gotos skips to below if false
            layers[lc-1].untouch_data(xl,yt,xr,yb);
        }
        
        next_layer:
        // This is the essence of the quadtree method:
        // If any of the upper layers do not have a collision object, we do not have to check the layer beneath.
        // Thus frequently giving us the opportunity to abort testing early.
        if(isCol == false) {
            return;
        }
    }// for(layers)
}

/**
 * Helper function to set a collision region to colliding
 */
void cColMap::setbox(cVector tl, cVector br, sColSectorInstance *data)
{
	int l;	// Current layer
	cLayer *cl;
	
	// Bounding box indexes to use	
	int xl,xr;
	int yt,yb;
	
	// Iterate through all layers
	for(l=0;l<lc;l++) {
		cl = &layers[l];
		
		// Get the indexes of the box
        // And make sure they're capped
        yt = cl->cap(  cl->getyi(tl.y)-1  );
        xl = cl->cap(  cl->getxi(tl.x)-1  );
        yb = cl->cap(  cl->getyi(br.y)+1  );
        xr = cl->cap(  cl->getxi(br.x)+1  );
		
		// Iterate through data
		int ty,tx;
		for(ty=yt; ty < yb; ty++) {
			for(tx=xl; tx < xr; tx++) {
				// Set flag at index
				cl->set(tx,ty);
				
				// Push the data, if bottom layer
				if(l==lc-1)
                    cl->data[ty][tx]->push_back(data);
			}
		}
	}
	
}

/**
 * Function to clear out all data currently in a collision map.
 */
void cColMap::clear()
{
    for(int l=0;l<lc; l++) {
        cLayer *cl = &layers[l];
        
        for(int yi=0;yi<cl->xys;yi++) {
            for(int xi=0;xi<cl->xys;xi++) {
                // Reset bits, this is slow, but for std::vector<bool>, there is no other way
                cl->data[yi][xi] = false;
                
                // Clear data from map
                if(l==lc-1)
                    cl->data[yi][xi]->clear();
            }
        }
    }
}
