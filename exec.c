/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:58:15 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/20 10:58:15 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int    exec(char *name, char **envp, char	**split)
{
    t_env_var	*var;
    char        **fold;
    int         index;
    struct stat a;
    pid_t       b;
    int fd[2];
    // int fd = open("teste.txt", O_WRONLY);
    int n;

    pipe(fd);
    index = 0;
    var = env_get_by_name("PATH");
    fold = ft_split(var->value, ':');
    b = 0;
    n = stat(name, &a);
    while (index < ft_split_length(fold))
    {
        fold[index] = ft_strjoin_free(fold[index], "/", FT_STRJOIN_FREE_FIRST);
        fold[index] = ft_strjoin_free(fold[index], name, FT_STRJOIN_FREE_FIRST);
        if (!stat(fold[index], &a) || !n)
        {
            b = fork();
            if (!b)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                execve(!n ? name : fold[index], split, envp);
            }
            ft_split_free(&fold);
            return (1);
        }
        index++;
    }
    ft_split_free(&fold);
    return (b ? 1 : 0);
}
