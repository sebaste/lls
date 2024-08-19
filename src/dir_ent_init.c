#include <dirent.h>

#include "lls.h"

int init_dir_entries(const Flags *flags, const char *dir, Entry **entries)
{
    DIR *d = opendir(dir);

    if (!open_dir(dir, &d)) {
        return -1;
    }

    int entry_count = 0;
    struct dirent *dir_entry;
    while ((dir_entry = readdir(d)) != NULL) {
        if (filter_str(flags, dir_entry->d_name)) {
            entry_count++;
        }
    }
    closedir(d);

    if (entry_count > 0) {
        *entries = (Entry*)malloc(entry_count * sizeof(Entry));
        if (*entries == NULL) {
            print_err("Memory allocation failed");
            return -1;
        }
    }

    return entry_count;
}
