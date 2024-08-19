#include <stdio.h>

#include "lls.h"

void print_dir_entries_long(const Flags *flags, Entry *entries, int nm)
{
    for (int i = 0; i < nm; i++) {
        print_dir_entry_long(flags, entries[i]);
    }
    printf("\n");
}

void print_dir_entries_reg(Entry *entries, int nm)
{
    for (int i = 0; i < nm; i++) {
        print_dir_entry_reg(entries[i]);
    }
    printf("\n\n");
}

void print_dir_entries(const Flags *flags, const char *dir, Entry *entries, int nm, int blocks_total)
{
    if (flags->l || flags->g) {
        if (flags->R || flags->mult_args || flags->init_non_flag_args_nm > 1) {
            printf("%s:\n", dir);
        }
        printf("total %d\n", blocks_total);
        print_dir_entries_long(flags, entries, nm);
    } else {
        if (flags->R || flags->mult_args) {
            printf("%s:\n", dir);
        }
        print_dir_entries_reg(entries, nm);
    }
}

void print_dir_entry_d(const Flags *flags, Entry dir, int is_last)
{
    if (flags->l || flags->g) {
        print_dir_entry_long(flags, dir);
    } else {
        print_dir_entry_reg(dir);
        if (is_last) {
            printf("\n");
        }
    }
}
