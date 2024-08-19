#include <linux/limits.h>

#include "custom_strlib.h"
#include "lls.h"

void swap_str_elems(char *a, char *b)
{
    char temp[PATH_MAX+1];

    custom_strcpy(temp, a);
    custom_strcpy(a, b);
    custom_strcpy(b, temp);
}

void swap_entry_elems(Entry *a, Entry *b)
{
    Entry temp = *a;
    *a = *b;
    *b = temp;
}
