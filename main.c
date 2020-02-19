/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:18:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:18:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main3(int argc, char **argv)
{
	t_arrlst *alst;

	alst = arraylist_create(2, NULL);
	for (size_t i = 0; i < 15; i++)
	{
		arraylist_add(alst, (void *)i);
		// ft_printf("added %d\n", (int)i);
	}
	arraylist_add(alst, (void *)1);
	arraylist_add(alst, (void *)2);
	arraylist_add(alst, (void *)3);
	for (size_t i = 0; i < alst->size; i++)
	{
		ft_printf("[%5d] = %d\n", (int)i, (int)(alst->items[i]));
	}
	arraylist_destroy(alst);
	return (EXIT_SUCCESS);
}

int
	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	env_initialize(envp);
	minishell_initialize(&shell, argv[0]);
	minishell_pre_loop(&shell);
	minishell_input_loop(&shell);
	return (EXIT_SUCCESS);
}
