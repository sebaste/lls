#include "custom_strlib.h"

void custom_strdel(char **str_ptr)
{
    if (str_ptr && *str_ptr)
    {
        free(*str_ptr);
        *str_ptr = NULL;
    }
}

size_t custom_strlen(const char *str)
{
    const char *start_ptr = str;
    while (*str)
        str++;
    return str - start_ptr;
}

char *custom_strnew(size_t size)
{
    char *new_str = (char *)malloc(size + 1);
    if (new_str == NULL)
        return NULL;
    custom_memset(new_str, '\0', size + 1);
    return new_str;
}

char *custom_strncpy(char *destination, const char *source, size_t nm)
{
    char *dest_start = destination;
    while (nm && *source)
    {
        *destination++ = *source++;
        nm--;
    }
    while (nm)
    {
        *destination++ = '\0';
        nm--;
    }
    return dest_start;
}

char *custom_strjoin(char const *str1, char const *str2)
{
    if (str1 == NULL || str2 == NULL)
        return NULL;
    size_t str1_len = custom_strlen(str1);
    size_t str2_len = custom_strlen(str2);
    char *joined_str = custom_strnew(str1_len + str2_len);
    if (joined_str)
    {
        custom_strncpy(joined_str, str1, str1_len);
        custom_strncpy(joined_str + str1_len, str2, str2_len);
    }
    return joined_str;
}

char *custom_strcpy(char *destination, const char *source)
{
    char *dest_start = destination;
    while (*source != '\0')
    {
        *destination++ = *source++;
    }
    *destination = '\0';
    return dest_start;
}

char *custom_strsub(char const *str, unsigned int start, size_t length)
{
    if (str == NULL)
        return NULL;
    size_t str_len = custom_strlen(str);
    if (start > str_len)
        return NULL;
    char *sub_str = (char*)malloc(length + 1);
    if (sub_str == NULL)
        return NULL;
    for (size_t i = 0; i < length; i++)
        sub_str[i] = str[start + i];
    sub_str[length] = '\0';
    return sub_str;
}

int custom_tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

int custom_strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}
