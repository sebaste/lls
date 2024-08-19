#include <sys/stat.h>

#include "custom_strlib.h"
#include "lls.h"

void get_dir_entries_name_full(const char *dir, const char *name, Entry **entries, int index)
{
    char *full_path;

    if (dir[custom_strlen(dir) - 1] != '/') {
        char *temp_path = custom_strjoin(dir, "/");
        full_path = custom_strjoin(temp_path, name);
        custom_strdel(&temp_path);
    } else {
        full_path = custom_strjoin(dir, name);
    }

    custom_strcpy((*entries)[index].name_full, full_path);
    custom_strdel(&full_path);
}

void get_dir_entries_stat(const Flags *flags, Entry *entry, int *blocks_total)
{
    struct stat s;

    if (lstat(entry->name_full, &s) == 0) {
        if (flags->t || flags->l) {
            entry->time_mod = s.st_mtim;
        }

        entry->mode = s.st_mode;

        // ls uses a block-size of 1024 B by default (can be changed with the
        // --block-size flag), while struct stat has blocks of size 512 B.
        *blocks_total += s.st_blocks / 2;
    } else {
        print_err_file_access(entry->name_full);
    }
}

void get_dir_entries(const Flags *flags, const char *dir, Entry **entries, int *blocks_total)
{
    *blocks_total = 0;

    DIR *d = opendir(dir);
    if (d == NULL) {
        print_err_file_access(dir);
        return;
    }

    int i = 0;
    struct dirent *de;
    while ((de = readdir(d)) != NULL) {
        if (filter_str(flags, de->d_name)) {
            custom_strcpy((*entries)[i].name, de->d_name);
            get_dir_entries_name_full(dir, de->d_name, entries, i);
            get_dir_entries_stat(flags, &((*entries)[i]), blocks_total);
            i++;
        }
    }

    closedir(d);
}
