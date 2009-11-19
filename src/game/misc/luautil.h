#ifndef LUAUTIL_H
#define LUAUTIL_H
#include <map>
#include "../lua.h"
#include "log.h"

/**
 * Class to register variables to a LUA script "class"
 * in such a way that the LUA-C++ bridge is always synchronized
 */
class cLuaClass {
	private:
		typedef unsigned int uint_hash;
		
		enum varType {
            varInt,
            varDouble,
            varVector
		};
		
		struct sVar {
			sVar() {}
			sVar(int *i) : type(varInt) { var.i = i; }
			sVar(double *d) : type(varDouble) { var.d = d; }
			sVar(cVector *v) : type(varVector) { var.v = v; }
			
			varType type;
			union {
				int *i;
				double *d;
				cVector *v;
			}var;
		};
	
		/// Creates a hash value for a variable name
		uint_hash hashFunc(const char *varname) {
            int len = strlen(varname);
            
            const unsigned int m = 0x5bd1e995;
            const int r = 24;
            
            uint_hash h = 0;
            
            while(len >= 4) {
                uint_hash k = *(uint_hash *)varname;
                
                k *= m;
                k ^= k >> r;
                k *= m;
                
                h *= m;
                h ^= k;
                
                varname += 4;
                len -= 4;
            }
            
            switch(len) {
                case 3: h^=varname[2] << 16;
                case 2: h^=varname[1] << 8;
                case 1: h^=varname[0];
                h *= m;
            }
            
            h ^= h >> 13;
            h *= m;
            h ^= h >> 15;
            
            return h;
		}
		
		/// Associates a hash value with a variable
		std::map<uint_hash, sVar> varm;
		
		/// @name Functions for the metatable
		//@{
			/// Shared code function
			sVar *getVar(const char *str) {
				uint_hash hash = hashFunc(str);
				
				// Find the variable
				std::map<uint_hash, sVar>::iterator i;
				i = varm.find(hash);
				if(i == varm.end()) {
					LOGU(LERR, "LUA script attempting to call nonexistent class variable");
					return NULL;
				}
				
				// Return the variable
				return &i->second;
			}
			
			/// Retrieves a class variable
			static int getClass(lua_State *L) {
				cLuaClass *self = *(cLuaClass**)lua_touserdata(L, 1);
				
				// Get the variable, assume it exists
				sVar *v = self->getVar(lua_tostring(L,2));
				switch(v->type) {
					case varInt:
						lua_pushnumber(L, *v->var.i);
						
						return 1;
					break;
					
					case varDouble:
						lua_pushnumber(L, *v->var.d);
						
						return 1;
					break;
					
					case varVector:
						lua_newtable(L);
						lua_pushnumber(L, v->var.v->x); lua_rawseti(L, -2, 1);
						lua_pushnumber(L, v->var.v->y); lua_rawseti(L, -2, 2);
						return 1;
					break;
				}
				
				return 1;
			}
			
			/// Sets a class variable
			static int setClass(lua_State *L) {
				cLuaClass *self = *(cLuaClass**)lua_touserdata(L, 1);
				
				// Get the variable, assume it exists
				sVar *v = self->getVar(lua_tostring(L,2));
				
				switch(v->type) {
					case varInt:
						*v->var.i = luaL_checkint(L,3);
					break;
					
					case varDouble:
						*v->var.d = luaL_checknumber(L,3);
					break;
					
					case varVector:
						if(lua_istable(L,3)) {
							lua_rawgeti(L,3, 1); v->var.v->x = lua_tonumber(L,-1); lua_pop(L,1);
							lua_rawgeti(L,3, 2); v->var.v->y = lua_tonumber(L,-1); lua_pop(L,1);
						}
					break;
				}
				
				return 0;
			}
		//@}
		
	public:
		/// Registers this object into the lua state \p L, with a classname \p name
		void register_self(lua_State *L, const char *name) {
			// A LUA userdata pointer to this class 
			cLuaClass **data = (cLuaClass **)lua_newuserdata(L, sizeof(cLuaClass**));
			*data = this;
			
			luaL_newmetatable(L, name);           	// Create a metatable
			lua_pushcfunction(L, getClass); lua_setfield(L, -2, "__index");
			lua_pushcfunction(L, setClass); lua_setfield(L, -2, "__newindex");
			lua_setmetatable(L,-2);                 // Append this metatable to the userdata
			lua_setglobal(L, name);               	// Designate a name to this data metatable [hides the userdata within the table]
		}
		
		/// @name Registration of variables to class
		//@{
			void register_int(const char *varname, int *varptr)
			{	varm[hashFunc(varname)] = sVar(varptr); }
			
			void register_double(const char *varname, double *varptr)
			{	varm[hashFunc(varname)] = sVar(varptr); }
			
			void register_vector(const char *varname, cVector *varptr)
			{	varm[hashFunc(varname)] = sVar(varptr); }
		//@}
};

#endif // LUAUTIL_H
