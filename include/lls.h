#ifndef LLS_H
#define LLS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>

// NAME_MAX and PATH_MAX (system max number of characters).
#include <linux/limits.h>

#define ORDER_ASC 0
#define ORDER_DES 1

typedef struct Flags Flags;
struct Flags {
    int a;
    int d;
    int g;
    int G;
    int h;
    int l;
    int r;
    int R;
    int t;

    // Set if multiple directories are passed in as args.
    int mult_args;
    // The initial number of non-flag arguments (existing or not).
    int init_non_flag_args_nm;
};

typedef struct Entry Entry;
struct Entry {
    char name[PATH_MAX+1];
    char name_full[PATH_MAX+1];
    struct timespec time_mod;
    mode_t mode;
};

int filter_str(const Flags*, char*);
int get_args(int, char**, Flags*, Entry**, int*);
int init_dir_entries(const Flags*, const char*, Entry**);
int open_dir(const char*, DIR**);
int timespec_gt(struct timespec, struct timespec);
int timespec_lt(struct timespec, struct timespec);
void get_dir_entries(const Flags*, const char*, Entry**, int*);
void init_flags(Flags*);
void init_sort(Flags*, Entry**, int);
void print_dir_entries(const Flags*, const char*, Entry*, int, int);
void print_dir_entry_d(const Flags*, Entry, int);
void print_dir_entry_long(const Flags*, Entry);
void print_dir_entry_reg(Entry);
void print_err(const char*);
void print_err_file_access(const char*);
void print_err_invalid_arg(const char);
void print_file_group_rights(mode_t);
void print_file_mode(mode_t);
void print_file_others_rights(mode_t);
void print_file_owner_rights(mode_t);
void print_file_owners(const Flags*, uid_t, gid_t);
void print_file_size(const Flags*, off_t);
void print_file_mod_time(const time_t*);
void print_sym_link_name(const char*);
void sort_entries_array_date(const Flags*, Entry**, int);
void sort_entries_array_reg(const Flags*, Entry**, int);
void sort_str_array_reg(const Flags*, char***, int);
void swap_entry_elems(Entry*, Entry*);
void swap_str_elems(char*, char*);

#endif
