//Driver file for the program 

#include "do_ls.h"
#lnclude <stdio.h>

int main(int ac, char *av[]) 
{
    if (ac == 1)
        do_ls(".");
    else
        while (--ac) 
        {
            printf("%s:\n", *++av);
            do_ls(*av);
        }
    return 0;
}
