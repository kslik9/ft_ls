#include "ft_ls.h"

static void init_ls(t_ls *ls)
{
    ls->flags = 0;
    ls->paths = NULL;
    ls->path_count = 0;
}

static void parse_arguments(int argc, char **argv, t_ls *ls)
{
    int i, j;

    // First parse flags
    for (i = 1; i < argc && argv[i][0] == '-' && argv[i][1] != '\0'; i++) {
        for (j = 1; argv[i][j]; j++) {
            if (argv[i][j] == 'l') ls->flags |= FLAG_L;
            else if (argv[i][j] == 'R') ls->flags |= FLAG_R;
            else if (argv[i][j] == 'a') ls->flags |= FLAG_A;
            else if (argv[i][j] == 'r') ls->flags |= FLAG_r;
            else if (argv[i][j] == 't') ls->flags |= FLAG_T;
            else {
                ft_putstr("ft_ls: invalid option -- '");
                ft_putchar(argv[i][j]);
                ft_putendl("'");
                exit(1);
            }
        }
    }

    ls->path_count = argc - i;
    if (ls->path_count == 0) {
        ls->paths = malloc(sizeof(char*));
        ls->paths[0] = ft_strdup(".");
        ls->path_count = 1;
    } else {
        ls->paths = malloc(sizeof(char*) * ls->path_count);
        int k = 0;
        for (; i < argc; i++) {
            ls->paths[k++] = ft_strdup(argv[i]);
        }
    }
}

static void cleanup_ls(t_ls *ls)
{
    int i;
    
    if (ls->paths)
    {
        for (i = 0; i < ls->path_count; i++)
        {
            if (ls->paths[i])
                free(ls->paths[i]);
        }
        free(ls->paths);
    }
}

int main(int argc, char **argv)
{
    t_ls ls;
    
    init_ls(&ls);
    parse_arguments(argc, argv, &ls);
    ft_ls(&ls);
    cleanup_ls(&ls);
    
    return (0);
}