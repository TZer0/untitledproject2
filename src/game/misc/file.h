/**
 * File: file.h
 *
 * Description: Header file for miscellaneous file related functions
 */
#ifndef DANFILE_H
#define DANFILE_H
// Global includes
#include <allegro.h>
#include <list>
#include <string>

class cmFile {
    char *datadir;
    char *execdir;
    public:
    cmFile() {
        datadir=NULL;
        execdir=NULL;
    }
    double read_double(PACKFILE *fp);
    char *read_string(PACKFILE *fp);

    void set_data_directory(const char *dir);
    std::string execdir_strip(const char *dir);
    std::list<std::string> dirRecursiveGet(const char *tdir, const char *suffix);
    std::string get_filename(const char *basedir, const char *filename);

    char *get_script(const char *file);
};

#endif

