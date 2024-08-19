#include <stdio.h>

void print_err(const char *str)
{
    fprintf(stderr,
            "ls: operation failed: %s\n",
            str
        );
}

void print_err_file_access(const char *str)
{
    fprintf(stderr,
            "ls: cannot access '%s': No such file or directory\n",
            str
        );
}

void print_err_invalid_arg(const char c)
{
    fprintf(stderr,
        "ls: invalid option -- '%c'\n",
        c
    );
}
