#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

# define FLAG_L     (1 << 0)  // -l long format
# define FLAG_R     (1 << 1)  // -R recursive
# define FLAG_A     (1 << 2)  // -a show hidden files
# define FLAG_r     (1 << 3)  // -r reverse order
# define FLAG_T     (1 << 4)  // -t sort by time

typedef struct s_file
{
    char            *name;
    char            *path;
    struct stat     stat;
    struct s_file   *next;
}                   t_file;

typedef struct s_ls
{
    int     flags;
    char    **paths;
    int     path_count;
}           t_ls;

// Core functions
void    ft_ls(t_ls *ls);
void    process_directory(const char *path, t_ls *ls, int is_recursive);
void    process_file(const char *path, t_ls *ls);

// File list management
t_file  *create_file_node(const char *name, const char *path);
void    add_file_to_list(t_file **head, t_file *new_file);
void    free_file_list(t_file *head);
t_file  *sort_files(t_file *head, int flags);

// Display functions
void    display_files(t_file *files, t_ls *ls, const char *dir_path);
void    display_long_format(t_file *file);
void    display_simple_format(t_file *files);

// Utility functions
int     parse_flags(const char *arg);
char    *ft_strjoin(const char *s1, const char *s2);
char    *ft_strdup(const char *s);
char    *ft_strcpy(char *dest, const char *src);
char    *ft_strcat(char *dest, const char *src);
int     ft_strcmp(const char *s1, const char *s2);
size_t  ft_strlen(const char *s);
void    ft_putstr(const char *s);
void    ft_putchar(char c);
void    ft_putendl(const char *s);

// Error handling
void    print_error(const char *path, const char *message);
void    handle_stat_error(const char *path);

// File type and permissions
char    get_file_type(mode_t mode);
void    get_permissions(mode_t mode, char *perms);
char    *get_time_string(time_t time);

#endif