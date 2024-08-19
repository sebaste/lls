#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "custom_strlib.h"
#include "lls.h"

void rec_dir(const Flags *flags, Entry *entries, int nm);

void ls_rec_sort(const Flags *flags, Entry **entries, int nm)
{
    if (flags->t)
        sort_entries_array_date(flags, entries, nm);
    else
        sort_entries_array_reg(flags, entries, nm);
}

void ls_rec(const Flags *flags, Entry *dir, int is_last)
{
    // Only go through the dir entries and list them, nothing else.
    // This skips -R.
    if (flags->d)
    {
        print_dir_entry_d(flags, *dir, is_last);
        return;
    }

    Entry *entries = NULL;
    int nm = init_dir_entries(flags, dir->name_full, &entries);
    if (nm < 0)
        return;

    int blocks_total;
    get_dir_entries(flags, dir->name_full, &entries, &blocks_total);

    if (nm > 1)
        ls_rec_sort(flags, &entries, nm);

    print_dir_entries(flags, dir->name_full, entries, nm, blocks_total);

    if (flags->R)
        rec_dir(flags, entries, nm);

    free(entries);
}

void rec_dir(const Flags *flags, Entry *entries, int nm)
{
    for (int i = 0; i < nm; i++)
    {
        if (custom_strcmp(entries[i].name, ".") == 0 || custom_strcmp(entries[i].name, "..") == 0)
            continue;

        if (S_ISDIR(entries[i].mode))
            ls_rec(flags, &entries[i], 0);
    }
}

void ls_start(const Flags *flags, Entry *dir, int is_last)
{
    if (S_ISDIR(dir->mode))
    {
        ls_rec(flags, dir, is_last);
    }
    else
    {
        print_dir_entry_d(flags, *dir, 0);
    }
}

int main(int argc, char *argv[])
{
    Flags flags;
    init_flags(&flags);

    Entry *arg_files = NULL;
    int arg_files_size;
    if (get_args(argc, argv, &flags, &arg_files, &arg_files_size))
        return 1;

    if (arg_files_size > 1)
        init_sort(&flags, &arg_files, arg_files_size);

    for (int dir_current = 0; dir_current < arg_files_size; dir_current++)
    {
        ls_start(&flags, &arg_files[dir_current], dir_current == arg_files_size - 1);
    }

    free(arg_files);
    return 0;
}
