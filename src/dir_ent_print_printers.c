#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "lls.h"

void print_sym_link_name(const char *path)
{
    char link_target[PATH_MAX + 1];
    ssize_t len = readlink(path, link_target, sizeof(link_target) - 1);
    if (len != -1) {
        link_target[len] = '\0';
        printf(" -> %s", link_target);
    } else {
        char err_message[256];
        sprintf(err_message, "readlink: %s", strerror(errno));
        print_err(err_message);
    }
}

void print_dir_entry_long(const Flags *flags, Entry entry)
{
    struct stat s;
    if (lstat(entry.name_full, &s) == -1) {
        char err_message[256];
        sprintf(err_message, "lstat: %s", strerror(errno));
        print_err(err_message);
        return;
    }

    print_file_mode(s.st_mode);
    print_file_owner_rights(s.st_mode);
    print_file_group_rights(s.st_mode);
    print_file_others_rights(s.st_mode);
    printf(" %lu", s.st_nlink);
    print_file_owners(flags, s.st_uid, s.st_gid);
    print_file_size(flags, s.st_size);
    print_file_mod_time(&s.st_mtime);
    printf(" %s", entry.name);

    if (S_ISLNK(s.st_mode)) {
        print_sym_link_name(entry.name_full);
    }

    printf("\n");
}

void print_dir_entry_reg(Entry entry)
{
    printf("%s", entry.name);
    printf("  ");
}
