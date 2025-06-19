#include "ft_ls.h"

char *ft_strcpy(char *dest, const char *src)
{
    int i = 0;
    
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *ft_strcat(char *dest, const char *src)
{
    int dest_len = ft_strlen(dest);
    int i = 0;
    
    while (src[i])
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return (dest);
}

char *ft_strjoin(const char *s1, const char *s2)
{
    size_t len1, len2;
    char *result;
    size_t i, j;
    
    if (!s1 || !s2)
        return (NULL);
    
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    
    result = malloc(len1 + len2 + 1);
    if (!result)
        return (NULL);
    
    i = 0;
    while (i < len1)
    {
        result[i] = s1[i];
        i++;
    }
    
    j = 0;
    while (j < len2)
    {
        result[i + j] = s2[j];
        j++;
    }
    
    result[i + j] = '\0';
    return (result);
}

char *ft_strdup(const char *s)
{
    size_t len;
    char *dup;
    size_t i;
    
    if (!s)
        return (NULL);
    
    len = ft_strlen(s);
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    
    return (dup);
}

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;
    
    if (!s1 || !s2)
        return (0);
    
    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    
    if (!s)
        return (0);
    
    while (s[len])
        len++;
    
    return (len);
}

void ft_putstr(const char *s)
{
    if (s)
        write(1, s, ft_strlen(s));
}

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putendl(const char *s)
{
    ft_putstr(s);
    ft_putchar('\n');
}

void print_error(const char *path, const char *message)
{
    ft_putstr("ft_ls: ");
    ft_putstr(path);
    ft_putstr(": ");
    ft_putendl(message);
}

void handle_stat_error(const char *path)
{
    ft_putstr("ft_ls: cannot access '");
    ft_putstr(path);
    ft_putstr("': ");
    ft_putendl(strerror(errno));
}