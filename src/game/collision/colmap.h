/**
 * \file colmap.h
 *
 * Description: Header file for collision map
 *
 */
#ifndef COLMAP_H
#define COLMAP_H
// Global includes
#include <vector>

#include "../misc/vector.h"

// Forward declarations
class cApplyCollision;

/**
 * Collision struct that is attached to all sectors
 * that the instance that owns this object intersects with.
 */
struct sColSectorInstance {
    public:
        sColSectorInstance() {ptr=NULL, hasTouched=false;}
        void *ptr;          ///< Pointer to the data object
        bool hasTouched;    ///< Internal flag that determines if this sector instance has been collided against
};

/**
 * Collision map class.
 * Keeps several layers with different resolution.
 * To be used as a highly efficient collision detection system
 * by reducing the number of neccesary collision tests by a significant
 * amount.
 */
class cColMap {
    private:
        /**
          * A layer of collision data.
          */
        class cLayer {
        public:
            /// @name Collision map data
            //@{
                /// @note I used the boost library's bitset [instead of a vector<bool> in my version of this, which is [much] faster
                /// but I want to avoid using boost [it is cumbersome] for this game. Though this is up for discussion.
                std::vector<std::vector<bool> > md; ///< Collision bitmap for sectors that contain a collision object
                
                std::vector< // Y axis
                    std::vector< // X axis
                        std::vector<struct sColSectorInstance*>* // Contents of a sector
                    >
                >data;  ///< The data contents of a sector
            //@}
            
            /// @name Layer size and position
            //@{
                double xw,yw;       ///< Unit size of each layer sector
                int xys;            ///< Size of the collision map in sectos
            //@}
            
            /// @name Functions
            //@{
                /// Prevents a sector index from being outside the map
                int cap(int ind) { if(ind<0) ind=0; else if(ind>=xys) ind=xys; return ind; }
                
                bool get(int xi,int yi) { return(md[yi][xi]); }
                void set(int xi,int yi) { md[yi][xi] = true;  }
            
                /// @name Returns the sector position index from a game-unit position
                //@{
                    int getxi(double x) { return(int(floor(x/xw))); }
                    int getyi(double y) { return(int(floor(y/yw))); }
                //@}
                
                /// Untouches a part of the bottom [data] layer denoted by the box
                void untouch_data(int tlx, int tly, int brx, int bry) {
                    for(int iy=tly;iy<=bry;iy++) {
                        for(int ix=tlx;ix<=brx;ix++) {
                            for(std::vector<sColSectorInstance*>::iterator i = data[iy][ix]->begin(); i != data[iy][ix]->end(); i++) {
                                (*i)->hasTouched = false;
                            }
                        }
                    }
                }
            //@}
        };
        
        int lc;                 ///< Number of collision layers
        cLayer *layers;         ///< Internal map of collision layers

	public:
		/// Collision map constructor
		cColMap(int depth, double w,double h);
		
		/// Function to resize the collision map to new parameters
		/// Useful on map change
		void resize(double w,double h);
		
		/// @name Interacting with the map
		//@{
            /// Assigns collision data to a specific position
            void set(cVector pos, bool v, sColSectorInstance *data);
		
            /// Assign collision data to the box denoted by tl, br
            /// \param tl Top left corner of box
            /// \param br Bottom right corner of the box
            void setbox(cVector tl, cVector br, sColSectorInstance *data);
        //@}
		
		/// @name Collision testing
		//@{
            // Tests for collision in a box
            void checkbox(cVector tl, cVector br, cApplyCollision *aplcol);
            std::vector<sColSectorInstance*> *checkpoint(cVector pt);
        //@}
		
		/// @name Misc finctions
		//@{
            // Helper function to clean out a collision map
            void clear();
        //@}
};


#endif
