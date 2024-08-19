#include "lls.h"

void init_flags(Flags *flags)
{
    flags->a = 0;
    flags->d = 0;
    flags->g = 0;
    flags->G = 0;
    flags->h = 0;
    flags->l = 0;
    flags->r = 0;
    flags->R = 0;
    flags->t = 0;
    flags->mult_args = 0;
    flags->init_non_flag_args_nm = 0;
}

void init_sort(Flags *flags, Entry **arg_files, int arg_files_size)
{
    flags->mult_args = 1;

    if (flags->t)
        sort_entries_array_date(flags, arg_files, arg_files_size);
    else
        sort_entries_array_reg(flags, arg_files, arg_files_size);
}
