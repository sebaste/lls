#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "custom_strlib.h"
#include "lls.h"

// Set the minimum chars to be used. Padding with ' ' will be used up until this number.
// This is to make the formatting look better when ls lists more than one element.
// Example: "32" -> "    32".
// A better method is to go through all the elements in a directory listing, get the longest existing string of
// the given type and then set the min chars constant to its length.
#define MIN_CHARS_SIZE 8
#define MIN_CHARS_USER 7
#define MIN_CHARS_GROUP 7

void print_file_mode(mode_t mode)
{
    if (S_ISBLK(mode))
        printf("b");
    else if (S_ISCHR(mode))
        printf("c");
    else if (S_ISDIR(mode))
        printf("d");
    else if (S_ISFIFO(mode))
        printf("p");
    else if (S_ISLNK(mode))
        printf("l");
    else if (S_ISREG(mode))
        printf("-");
    else if (S_ISSOCK(mode))
        printf("s");
}

void print_file_owners(const Flags *flags, uid_t uid, gid_t gid)
{
    if (!flags->g)
    {
        struct passwd *pwd = getpwuid(uid);
        if (pwd)
            printf(" %*s", MIN_CHARS_USER, pwd->pw_name);
    }

    if (!flags->G)
    {
        struct group *grp = getgrgid(gid);
        if (grp)
            printf(" %*s", MIN_CHARS_GROUP, grp->gr_name);
    }
}

void print_file_size_h(off_t size_input)
{
    const char *units[] = {"K", "M", "G", "T"};
    double size = size_input;
    int unit_index = 0;

    while (size > 1024 && unit_index < 3)
    {
        size /= 1024;
        unit_index++;
    }

    printf(" %*.1f%s", MIN_CHARS_SIZE, size, units[unit_index]);
}

void print_file_size(const Flags *flags, off_t size)
{
    if (flags->h)
    {
        print_file_size_h(size);
    }
    else
    {
        printf(" %*ld", MIN_CHARS_SIZE, size);
    }
}

void print_file_mod_time(const time_t *mtime)
{
    char buf[32];
    custom_strcpy(buf, ctime(mtime));
    buf[custom_strlen(buf)-1] = '\0';
    char *str = custom_strsub(buf, 4, 12);
    printf(" %s", str);
    custom_strdel(&str);
}
