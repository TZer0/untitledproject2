/**
 * File: loadtemplate.h
 *
 * Description:	Template for loading systems
 */
#ifndef LOADTEMPLATE_H
#define LOADTEMPLATE_H
// Global includes
#include <string>
#include <map>
#include <list>

/**
 * Template for a loading system.
 * Contains functions to store, get, and retrieve
 * instances. All instances are stored in a private
 * map.
 */
template <class MapType>
class tLoadingSystem {
	private:
        /// All is stored in this map, each instance referenced by a string
		std::map<std::string, MapType> data;
	
	public:
        /**
         * Retrieves an instance from data.
         * @return The instance if found, otherwise NULL.
         */
		MapType get(std::string name)
			{ typename std::map<std::string,MapType>::iterator d;
				return
					(
						(d=data.find(name))
							==data.end() ?
						NULL : d->second
					);
			}
		
		/**
		 * Inserts an instance into the data map.
		 */
		void insert(std::string name, MapType item)
		{ data[name] = item; }
		
		/**
		 * Gets the start iterator for the data map
		 */
		typename std::map<std::string,MapType>::iterator iterate(void)
		{ return(data.begin()); }
		
		/**
		 * Gets the end iterator for the data map
		 */
		typename std::map<std::string,MapType>::iterator dataend(void)
		{ return(data.end()); }
		
		/// List of filenames to load
		std::list<std::string> filedb;
		typedef std::list<std::string>::iterator FileIterator;
};

#endif

