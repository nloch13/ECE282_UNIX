#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <sys/types.h>
#include <sys/stat.h>

void show_file_info(char *filename, struct stat *info_p);

#endif
