#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "lls.h"

int open_dir(const char *dir, DIR **d)
{
    *d = opendir(dir);
    if (*d == NULL)
    {
        print_err_file_access(dir);
        return 0;
    }
    return 1;
}

int filter_str(const Flags *flags, char *str)
{
    if (!flags->a && str[0] == '.')
    {
        return 0;
    }
    return 1;
}
