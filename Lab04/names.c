#include <pwd.h>
#include <grp.h>
#include <stdio.h>

/* 
*	returns pointer to username associated with uid, uses getpw()
*/

char *uid_to_name(uid_t uid) 
{
    struct passwd *pw_ptr;
    static char numstr[10];

    if ((pw_ptr = getpwuid(uid)) == NULL) 
    {
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    return pw_ptr->pw_name;
}

/*
*	returns pointer to group number gid. used getgrgid(3)
*/

char *gid_to_name(gid_t gid) 
{
    struct group *grp_ptr;
    static char numstr[10];

    if ((grp_ptr = getgrgid(gid)) == NULL) 
    {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    return grp_ptr->gr_name;
}
