#ifndef CUSTOM_STRLIB_H
#define CUSTOM_STRLIB_H

#include <stddef.h>
#include <stdlib.h>
#include "custom_memlib.h"

char *custom_strcpy(char*, const char*);
char *custom_strjoin(char const*, char const*);
char *custom_strncpy(char*, const char*, size_t);
char *custom_strnew(size_t);
char *custom_strsub(char const*, unsigned int, size_t);
int custom_strcmp(const char*, const char*);
int custom_tolower(int);
size_t custom_strlen(const char*);
void custom_strdel(char**);

#endif
