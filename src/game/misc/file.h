/**
 * File: file.h
 *
 * Description: Header file for miscellaneous file related functions
 *
 * (c)2009, by Raymond Loeberg
 */
#ifndef DANFILE_H
#define DANFILE_H
// Global includes
#include <allegro.h>
#include <list>
#include <string>

double read_double(PACKFILE *fp);
char *read_string(PACKFILE *fp);

void set_data_directory(const char *dir);
std::string execdir_strip(const char *dir);
std::list<std::string> dirRecursiveGet(const char *tdir, const char *suffix);
std::string get_filename(const char *basedir, const char *filename);

char *get_script(const char *file);

#endif
