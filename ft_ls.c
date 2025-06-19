#include "ft_ls.h"

void ft_ls(t_ls *ls)
{
    int i;
    struct stat st;
    
    for (i = 0; i < ls->path_count; i++)
    {
        if (stat(ls->paths[i], &st) == -1)
        {
            handle_stat_error(ls->paths[i]);
            continue;
        }
        
        if (S_ISDIR(st.st_mode))
        {
            if (ls->path_count > 1)
            {
                if (i > 0)
                    ft_putchar('\n');
                ft_putstr(ls->paths[i]);
                ft_putendl(":");
            }
            process_directory(ls->paths[i], ls, 0);
        }
        else
        {
            process_file(ls->paths[i], ls);
        }
    }
}

void process_directory(const char *path, t_ls *ls, int is_recursive)
{
    DIR *dir;
    struct dirent *entry;
    t_file *files = NULL;
    t_file *current;
    char *full_path;
    size_t path_len;
    
    dir = opendir(path);
    if (!dir)
    {
        print_error(path, "cannot open directory");
        return;
    }
    
    path_len = ft_strlen(path);
    
    while ((entry = readdir(dir)) != NULL)
    {
        // Skip hidden files if -a flag not set
        if (!(ls->flags & FLAG_A) && entry->d_name[0] == '.')
            continue;
        
        // Create full path
        full_path = malloc(path_len + ft_strlen(entry->d_name) + 2);
        if (!full_path)
            continue;
        
        ft_strcpy(full_path, path);
        if (path_len > 0 && path[path_len - 1] != '/')
        {
            full_path[path_len] = '/';
            full_path[path_len + 1] = '\0';
            ft_strcat(full_path, entry->d_name);
        }
        else
        {
            ft_strcat(full_path, entry->d_name);
        }
        
        t_file *new_file = create_file_node(entry->d_name, full_path);
        free(full_path);
        
        if (new_file)
            add_file_to_list(&files, new_file);
    }
    
    closedir(dir);
    
    if (files)
    {
        files = sort_files(files, ls->flags);
        display_files(files, ls, path);
        
        // Handle recursive flag
        if (ls->flags & FLAG_R)
        {
            current = files;
            while (current)
            {
                if (S_ISDIR(current->stat.st_mode) && 
                    ft_strcmp(current->name, ".") != 0 && 
                    ft_strcmp(current->name, "..") != 0)
                {
                    ft_putchar('\n');
                    ft_putstr(current->path);
                    ft_putendl(":");
                    process_directory(current->path, ls, 1);
                }
                current = current->next;
            }
        }
        
        free_file_list(files);
    }
}

void process_file(const char *path, t_ls *ls)
{
    t_file *file = create_file_node(path, path);
    
    if (file)
    {
        display_files(file, ls, NULL);
        free_file_list(file);
    }
}