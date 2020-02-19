#include "minishell2.h"

int    exec(char *name, char **envp, char		**split)
{
    t_env_var	*var;
    char        **fold;
    int         index;
    struct stat a;

    index = 0;
    var = env_get_by_name("PATH");
    fold = ft_split(var->value, ':');
    while (index < ft_split_length(fold))
    {
        fold[index] = ft_strjoin(fold[index], "/");
        fold[index] = ft_strjoin(fold[index], name);

        if (!stat(fold[index], &a))
        {
            execve(fold[index], split, envp);
            ft_split_free(&fold);
            return (1);
        }
        index++;
    }
    printf("CACA");
    ft_split_free(&fold);
    return (0);
}