#include "ft_ls.h"

t_file *create_file_node(const char *name, const char *path)
{
    t_file *new_file;
    
    new_file = malloc(sizeof(t_file));
    if (!new_file)
        return (NULL);
    
    new_file->name = ft_strdup(name);
    new_file->path = ft_strdup(path);
    new_file->next = NULL;
    
    if (!new_file->name || !new_file->path)
    {
        if (new_file->name)
            free(new_file->name);
        if (new_file->path)
            free(new_file->path);
        free(new_file);
        return (NULL);
    }
    
    if (lstat(path, &new_file->stat) == -1)
    {
        handle_stat_error(path);
        free(new_file->name);
        free(new_file->path);
        free(new_file);
        return (NULL);
    }
    
    return (new_file);
}

void add_file_to_list(t_file **head, t_file *new_file)
{
    if (!*head)
    {
        *head = new_file;
        return;
    }
    
    new_file->next = *head;
    *head = new_file;
}

void free_file_list(t_file *head)
{
    t_file *temp;
    
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp->path);
        free(temp);
    }
}

static t_file *merge_files(t_file *left, t_file *right, int flags)
{
    t_file *result = NULL;
    t_file **tail = &result;
    int compare;
    
    while (left && right)
    {
        if (flags & FLAG_T)
        {
            if (left->stat.st_mtime > right->stat.st_mtime)
                compare = -1;
            else if (left->stat.st_mtime < right->stat.st_mtime)
                compare = 1;
            else if (left->stat.st_mtimespec.tv_nsec > right->stat.st_mtimespec.tv_nsec)
                compare = -1;
            else if (left->stat.st_mtimespec.tv_nsec < right->stat.st_mtimespec.tv_nsec)
                compare = 1;
            else
                compare = ft_strcmp(left->name, right->name);

        }
        else
        {
            compare = ft_strcmp(left->name, right->name);
        }
        
        if (flags & FLAG_r)
            compare = -compare;
        
        if (compare <= 0)
        {
            *tail = left;
            left = left->next;
        }
        else
        {
            *tail = right;
            right = right->next;
        }
        tail = &(*tail)->next;
    }
    
    *tail = left ? left : right;
    return (result);
}

static t_file *merge_sort_files(t_file *head, int flags)
{
    t_file *slow;
    t_file *fast;
    t_file *prev;
    t_file *left;
    t_file *right;
    
    if (!head || !head->next)
        return (head);
    
    // Find middle using slow/fast pointers
    slow = fast = head;
    prev = NULL;
    
    while (fast && fast->next)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Split the list
    prev->next = NULL;
    left = head;
    right = slow;
    
    // Recursively sort both halves
    left = merge_sort_files(left, flags);
    right = merge_sort_files(right, flags);
    
    // Merge the sorted halves
    return (merge_files(left, right, flags));
}

t_file *sort_files(t_file *head, int flags)
{
    return (merge_sort_files(head, flags));
}