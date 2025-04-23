/*
*	list files in directory called dirname
*/


#include <stdio.h>
#include <dirent.h>
#include "dostat.h"

void do_ls(char dirname[]) 
{
    DIR *dir_ptr;      /*the directory*/
    struct dirent *direntp;   /*each entry*/
    char path[1024];

    if ((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls3: cannot open %s\n", dirname);
    else 
    {
        while ((direntp = readdir(dir_ptr)) != NULL) //Bug fix to pass the whole path 
        {
            snprintf(path, sizeof(path), "%s/%s", dirname, direntp->d_name);
            dostat(path);
        }
        closedir(dir_ptr);
    }
}
