#include <stdio.h>
#include <sys/stat.h>
#include "file_info.h"

void dostat(char *filename) 
{
    struct stat info;
    if (stat(filename, &info) == -1)    /*cannot stat */
        perror(filename);               /*say who */
    else                                /*else show info  */
        show_file_info(filename, &info);
}
