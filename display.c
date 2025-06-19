#include "ft_ls.h"

#include "ft_ls.h"

static void ft_putnbr(long n)
{
    if (n < 0)
    {
        ft_putchar('-');
        n = -n;
    }
    if (n >= 10)
        ft_putnbr(n / 10);
    ft_putchar('0' + (n % 10));
}

static void print_padded_string(const char *str, int width, int left_align)
{
    int len = ft_strlen(str);
    int padding = width - len;
    
    if (!left_align && padding > 0)
    {
        while (padding--)
            ft_putchar(' ');
    }
    
    ft_putstr(str);
    
    if (left_align && padding > 0)
    {
        while (padding--)
            ft_putchar(' ');
    }
}

void display_files(t_file *files, t_ls *ls, const char *dir_path)
{
    if (ls->flags & FLAG_L)
    {
        // Calculate total blocks for -l format
        long total_blocks = 0;
        t_file *current = files;
        
        while (current)
        {
            total_blocks += current->stat.st_blocks;
            current = current->next;
        }
        
        ft_putstr("total ");
        ft_putnbr(total_blocks / 2); // Convert to 1K blocks
        ft_putchar('\n');
        
        current = files;
        while (current)
        {
            display_long_format(current);
            current = current->next;
        }
    }
    else
    {
        display_simple_format(files);
    }
}

void display_long_format(t_file *file)
{
    char perms[11];
    char *time_str;
    struct passwd *pwd;
    struct group *grp;
    
    // File type and permissions
    perms[0] = get_file_type(file->stat.st_mode);
    get_permissions(file->stat.st_mode, perms + 1);
    perms[10] = '\0';
    
    // Get user and group names
    pwd = getpwuid(file->stat.st_uid);
    grp = getgrgid(file->stat.st_gid);
    
    // Get time string
    time_str = get_time_string(file->stat.st_mtime);
    
    // Print in long format using only allowed functions
    ft_putstr(perms);
    ft_putchar(' ');
    
    // Print number of links (right-aligned, width 3)
    ft_putnbr((long)file->stat.st_nlink);
    ft_putchar(' ');
    
    // Print user name (left-aligned, width 8)
    print_padded_string(pwd ? pwd->pw_name : "unknown", 8, 1);
    ft_putchar(' ');
    
    // Print group name (left-aligned, width 8)
    print_padded_string(grp ? grp->gr_name : "unknown", 8, 1);
    ft_putchar(' ');
    
    // Print file size (right-aligned, width 8)
    ft_putnbr((long)file->stat.st_size);
    ft_putchar(' ');
    
    // Print time
    ft_putstr(time_str);
    ft_putchar(' ');
    
    // Print filename
    ft_putstr(file->name);
    
    // Handle symbolic links
    if (S_ISLNK(file->stat.st_mode))
    {
        char link_target[1024];
        ssize_t len = readlink(file->path, link_target, sizeof(link_target) - 1);
        if (len != -1)
        {
            link_target[len] = '\0';
            ft_putstr(" -> ");
            ft_putstr(link_target);
        }
    }
    
    ft_putchar('\n');
    free(time_str);
}

void display_simple_format(t_file *files)
{
    t_file *current = files;

    while (current)
    {
        ft_putstr(current->name);
        if (current->next)
        {
            ft_putchar(' ');
            ft_putchar(' ');
            ft_putchar(' ');
            ft_putchar(' ');
        }
        current = current->next;
    }
    ft_putchar('\n');
}

char get_file_type(mode_t mode)
{
    if (S_ISDIR(mode))
        return ('d');
    else if (S_ISLNK(mode))
        return ('l');
    else if (S_ISBLK(mode))
        return ('b');
    else if (S_ISCHR(mode))
        return ('c');
    else if (S_ISFIFO(mode))
        return ('p');
    else if (S_ISSOCK(mode))
        return ('s');
    else
        return ('-');
}

void get_permissions(mode_t mode, char *perms)
{
    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';
    
    // Handle special permissions
    if (mode & S_ISUID)
        perms[2] = (mode & S_IXUSR) ? 's' : 'S';
    if (mode & S_ISGID)
        perms[5] = (mode & S_IXGRP) ? 's' : 'S';
    if (mode & S_ISVTX)
        perms[8] = (mode & S_IXOTH) ? 't' : 'T';
}

char *get_time_string(time_t file_time)
{
    char *time_str = ctime(&file_time);
    char *result;
    time_t current_time;
    double diff;
    
    if (!time_str)
        return (ft_strdup("unknown"));
    
    current_time = time(NULL);
    diff = difftime(current_time, file_time);
    
    result = malloc(13);  // "Mon  1 12:34" or "Mon  1  2023"
    if (!result)
        return (ft_strdup("unknown"));
    
    // Format: "Mon dd HH:MM" for recent files, "Mon dd  yyyy" for old files
    if (diff < 6 * 30 * 24 * 3600)  // 6 months
    {
        strncpy(result, time_str + 4, 12);
        result[12] = '\0';
    }
    else
    {
        strncpy(result, time_str + 4, 7);
        strncpy(result + 7, time_str + 19, 5);
        result[12] = '\0';
    }
    
    return (result);
}