/**
 * File: file.cpp
 *
 * Description:    Miscellaneous functions to interact with files
 */
// Global includes
#include <math.h>
#include "../port.h"
#include <string>

// Other includes
#include "file.h"
#include "../game.h"

#define DATADIR_BUF_SIZE 1024

using namespace std;

/**
 * Reads a double float from a packfile.
 * Reads first a 1-byte length integer, then a string of that length
 * @returns A direct conversion of the loaded string
 */
double cmFile::read_double(PACKFILE *fp)
{
    int len;
    char str[256];
    
    len = pack_getc(fp);
    memset(str,0,len+1);
    pack_fread(str,len,fp);
    return(atof(str));
}

/**
 * Reads a string from a packfile
 * Reads first a 4-byte length integer, then a string of that same length
 * @returns A new memory block with the loaded string, null-terminated
 */
char *cmFile::read_string(PACKFILE *fp)
{
    int len;
    char *str;
    
    len = pack_igetl(fp);
    str = new char[len+1];
    memset(str,0,len+1);
    pack_fread(str,len,fp);
    return(str);
}

/**
 * Retrieves the executable directory, and appends the data directory to it.
 */
void cmFile::set_data_directory(const char *dir)
{
    // Give the data directory some memory
    if(datadir != NULL) delete datadir;
    datadir = new char[DATADIR_BUF_SIZE];
    if(execdir != NULL) delete execdir;
    execdir = new char[DATADIR_BUF_SIZE];
    
    memset(datadir,0,DATADIR_BUF_SIZE);
    memset(execdir,0,DATADIR_BUF_SIZE);
    
    // We've first got to retrieve the executable directory
    get_executable_name(execdir, DATADIR_BUF_SIZE);
    
    // Then we replace the directory with the datadir
    replace_filename(datadir,execdir, dir, DATADIR_BUF_SIZE);
    replace_filename(execdir,execdir, "", DATADIR_BUF_SIZE);
    printf("%s\n",datadir);
    
    // Then we clean it up, just in case
    if(datadir[strlen(datadir)-1]!='/') {
        int len = strlen(datadir);
        datadir[len] = '/';
        datadir[len+1] = '\0';
    }
    
    // And we're done \o/
    LOGL(LDEBUG,"Data directory: %s", execdir_strip(datadir).c_str());
}

/**
 * Recursively gets a list of all files in a specific directory and all subdirectories,
 * with the given patterm
 * @arg dir The directory to search in, not neccesary with a slash at the beginning
 * @arg pat The extension to answer to, ex. "png"
 * @returns A list of all filenames associated with the given suffix
 */
std::list<string> cmFile::dirRecursiveGet(const char *tdir, const char *pat)
{
    std::list<string> dirlist;
    std::list<string> filelist;
    struct al_ffblk fd;    // Allegro structure for the file
    string dirint;         // Internal string
    string curdir;        // Current directory
    std::list<string>::iterator cur;
    string dir;
    
    dirlist.clear(); filelist.clear();
    
    // Make sure there is no extra slash in the dir parameter
    dir = string(tdir);
    if(dir[dir.size()]=='/') dir.push_back('\0');
    
    // We will always search through the base directory
    dirlist.push_back(string(datadir)+string(dir)+string("/"));
    
    // Recursively get all subdirectories
    cur = dirlist.begin();
    dirint = string(*cur)+string("*");
    curdir = string(*cur)+string("/");
    LOGS(LDEBUG,"Retrieving directories..");
    while(cur != dirlist.end() && al_findfirst(dirint.c_str(), &fd, FA_ALL) == 0) {
        LOGS(LDEBUG,"\tCurrent directory: %s", execdir_strip((*cur).c_str()).c_str());
        do {
            // Ignore unwanted directories
            if(strcmp(fd.name,".")!=0 && strcmp(fd.name,"..")!=0) {
                if((fd.attrib & FA_DIREC)) {
                    LOGS(LDEBUG,"\t\tDirectory: %s", fd.name);
                    dirlist.push_back(((*cur)+string(fd.name)+string("/")));
                }
            }
        }while(al_findnext(&fd) == 0);
        al_findclose(&fd);
        cur++; // Go to next object in list
        if(cur != dirlist.end()) {
            dirint = string(*cur)+string("*");
            curdir = string(*cur)+string("");
        }
    }
    LOGS(LDEBUG,"Done retrieving directories");
    
    // From all directories, get filenames
    LOGS(LDEBUG,"Retrieving filenames..");
    for(cur=dirlist.begin();cur!=dirlist.end();cur++) {
        LOGS(LDEBUG,"\tFrom directory %s", execdir_strip((*cur).c_str()).c_str());
        // Get the first file in the directory, but go on if nothing is found (shouldn't happen)
        if(al_findfirst(((*cur)+string("*")).c_str(),&fd, FA_ALL)!=0) continue;
        
        do {
            if(!(fd.attrib & FA_DIREC) && strcmp(get_extension(fd.name),pat)==0) {
                LOGS(LDEBUG,"\t\tFilename: %s", fd.name);
                filelist.push_back((*cur)+string(fd.name));
            }
        }while(al_findnext(&fd)==0);
        al_findclose(&fd);
    }
    LOGS(LDEBUG,"Done retrieving filenames");
    
    return filelist;
}


/**
 * Gets a full script from file (text (not compiled)).
 * @returns The loaded text
 */
char *cmFile::get_script(const char *file)
{
    int len;
    char *script;
    PACKFILE *fp;
    
    // Load file into memory
    len = file_size_ex(file);
    script = new char[len+1];
    memset(script, 0, sizeof(char)*(len+1));
    
    if((fp = pack_fopen(file, "r"))==NULL) {
        LOGL(LERR, "Could not open file \'%s\' to get the script", file);
    }
    pack_fread(script, len, fp);
    pack_fclose(fp);
    
    return script;
}


/**
 * Strips off the executable directory position of a filename.
 * @returns A string consisting of the stripped filename
 */
std::string cmFile::execdir_strip(const char *file)
{
    string tmp;
    int i,len;
    tmp = string(file);
    i=0;
    len = strlen(execdir);
    while(i<len && tmp[i]==execdir[i]) {
        i++;
    }
    tmp.erase(0,i);
    
    return tmp;
}

/**
 * Appends the filename and basedir to the data directory
 * @returns A new string of the full filename for the file
 */
std::string cmFile::get_filename(const char *basedir, const char *filename)
{
    return(string(datadir)+string("/")+string(basedir)+string("/")+string(filename));
}
