#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "custom_strlib.h"
#include "lls.h"

int handle_args_flags(char arg, Flags *flags) {
    switch (arg) {
        case 'a': flags->a = 1; break;
        case 'd': flags->d = 1; break;
        case 'g': flags->g = 1; break;
        case 'G': flags->G = 1; break;
        case 'h': flags->h = 1; break;
        case 'l': flags->l = 1; break;
        case 'r': flags->r = 1; break;
        case 'R': flags->R = 1; break;
        case 't': flags->t = 1; break;
        default:
            print_err_invalid_arg(arg);
            return 1;
    }
    return 0;
}

int get_args_flags(int argc, char *argv[], Flags *flags, int *dirs_size)
{
    unsigned int count;

    int argc_flags = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && custom_strlen(argv[i]) > 1) {
            argc_flags++;
            count = 1;
            while (count < custom_strlen(argv[i])) {
                if (handle_args_flags(argv[i][count], flags)) {
                    return 1;
                }
                count++;
            }
        }
    }
    *dirs_size = argc - argc_flags - 1;
    return 0;
}

int get_args_dirs_get(const Flags *flags, const char *str_arg, Entry *entry, int *dirs_size)
{
    struct stat s;
    custom_memcpy(entry->name, str_arg, custom_strlen(str_arg) + 1);
    if (lstat(entry->name, &s) != 0) {
        print_err_file_access(entry->name);
        (*dirs_size)--;
        return 0;
    }
    entry->mode = s.st_mode;
    custom_memcpy(entry->name_full, str_arg, custom_strlen(str_arg) + 1);
    if (flags->t) {
        entry->time_mod = s.st_mtim;
    }
    return 1;
}

void get_args_dirs(int argc, char *argv[], Flags *flags, Entry **dirs, int *dirs_size)
{
    int j = 0;
    flags->init_non_flag_args_nm = *dirs_size;

    for (int i = 1; i < argc; i++) {
        // If the argument is not a flag, it is a pathname or a filename.
        if (argv[i][0] != '-' || custom_strlen(argv[i]) <= 1) {
            if (get_args_dirs_get(flags, argv[i], &(*dirs)[j], dirs_size)) {
                j++;
            }
        }
    }
}

// If the argument is not a flag, it has to be a directory.
// To get the size needed for the list of directories, simply
// take argc - (number of flags).
int get_args(int argc, char *argv[], Flags *flags, Entry **dirs, int *dirs_size)
{
    if (get_args_flags(argc, argv, flags, dirs_size)) {
        return 1;
    }

    if (*dirs_size > 0) {
        *dirs = (Entry*)malloc(*dirs_size * sizeof(Entry));
        if (*dirs == NULL) {
            print_err("Memory allocation failed");
            return 1;
        }
        get_args_dirs(argc, argv, flags, dirs, dirs_size);
    // If no directories provided as arguments, then ls will do a listing on
    // the CWD (".").
    } else {
        *dirs = (Entry*)malloc(sizeof(Entry));
        if (*dirs == NULL) {
            print_err("Memory allocation failed");
            return 1;
        }
        custom_strcpy((*dirs)[0].name, ".");
        custom_strcpy((*dirs)[0].name_full, ".");
        *dirs_size = 1;
        struct stat s;
        lstat((*dirs)[0].name_full, &s);
        (*dirs)[0].mode = s.st_mode;
    }

    return 0;
}
