#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void print_file_owner_rights(mode_t mode)
{
    if (mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    if (mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    if (mode & S_IXUSR)
        printf("x");
    else
        printf("-");
}

void print_file_group_rights(mode_t mode)
{
    if (mode & S_IRGRP)
        printf("r");
    else
        printf("-");
    if (mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if (mode & S_IXGRP)
        printf("x");
    else
        printf("-");
}

void print_file_others_rights(mode_t mode)
{
    if (mode & S_IROTH)
        printf("r");
    else
        printf("-");
    if (mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if (mode & S_IXOTH)
        printf("x");
    else
        printf("-");
}
