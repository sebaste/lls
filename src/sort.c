#include "custom_strlib.h"
#include "lls.h"

char* str_to_lower(const char *str)
{
    int len = custom_strlen(str);
    char *new = custom_strnew(len + 1);
    custom_strcpy(new, str);

    for (int i = 0; i < len; ++i)
    {
        new[i] = custom_tolower(new[i]);
    }

    return new;
}

void sort_str_array_reg(const Flags *flags, char ***arr, int array_size)
{
    for (int i = 0; i < array_size; ++i)
    {
        for (int j = 0; j < array_size; ++j)
        {
            char *a = str_to_lower((*arr)[i]);
            char *b = str_to_lower((*arr)[j]);

            if ((flags->r == 0 && custom_strcmp(a, b) < 0) || // Ascending
                (flags->r == 1 && custom_strcmp(a, b) > 0)) // Descending
            {
                swap_str_elems((*arr)[i], (*arr)[j]);
            }

            custom_strdel(&a);
            custom_strdel(&b);
        }
    }
}

void sort_entries_array_date(const Flags *flags, Entry **entries, int array_size)
{
    for (int i = 0; i < array_size; ++i)
    {
        for (int j = 0; j < array_size; ++j)
        {
            int comparison = (flags->r == 0) ? 
                             timespec_gt((*entries)[i].time_mod, (*entries)[j].time_mod) :
                             timespec_lt((*entries)[i].time_mod, (*entries)[j].time_mod);

            if (comparison)
            {
                swap_entry_elems(&((*entries)[i]), &((*entries)[j]));
            }
        }
    }
}

void sort_entries_array_reg(const Flags *flags, Entry **entries, int array_size)
{
    for (int i = 0; i < array_size; ++i)
    {
        for (int j = 0; j < array_size; ++j)
        {
            // ls by default uses lowercase for sorting comparisons.
            // Example: "Makefile" comes after "libft" by default.
            char *a = str_to_lower((*entries)[i].name);
            char *b = str_to_lower((*entries)[j].name);

            if ((flags->r == 0 && custom_strcmp(a, b) < 0) || 
                (flags->r == 1 && custom_strcmp(a, b) > 0))
            {
                swap_entry_elems(&((*entries)[i]), &((*entries)[j]));
            }

            custom_strdel(&a);
            custom_strdel(&b);
        }
    }
}
