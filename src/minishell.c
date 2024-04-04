/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:01:37 by laugarci          #+#    #+#             */
/*   Updated: 2023/11/22 13:39:36 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <sys/errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"

static void	proceed(char *input, t_list **list, t_list **env_lst, char **env)
{
	int	err;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	add_history(input);
	err = parse_input(input, env, list);
	if (!err)
	{
		*list = organize_list(*list);
		start_execution(*list, env_lst, env);
		ft_lstclear(list, (void *)free_token);
	}
	else
		set_or_return_exit_status(MODE_SET, err);
}

static int	main_loop(char *prompt, t_list **env_lst)
{
	char	*input;
	char	**environ;
	t_list	*list;

	environ = envlst_to_charpp(*env_lst);
	if (!environ)
		return (print_error_and_return("Cannot allocate memory\n", 12));
	signal_setup(STATE_READ);
	input = readline(prompt);
	if (!input)
		builtin_exit(ft_itoa(set_or_return_exit_status(MODE_RETURN, -1)));
	if (input[0] != '\0')
		proceed(input, &list, env_lst, environ);
	free_double((void **)environ);
	free(input);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	t_list	*env_lst;

	(void) argv;
	if (argc > 1)
		exit(1);
	env_lst = set_env(envp);
	if (!env_lst)
		return (print_error_and_return("Cannot allocate memory\n", 12));
	prompt = ft_strdup("minishell$ ");
	if (!prompt)
	{
		ft_lstclear(&env_lst, (void *)free_var);
		return (print_error_and_return("Cannot allocate memory\n", 12));
	}
	set_or_return_exit_status(MODE_SET, 0);
	while (42)
		if (main_loop(prompt, &env_lst))
			break ;
	ft_lstclear(&env_lst, (void *)free_var);
	free(prompt);
	clear_history();
	return (set_or_return_exit_status(MODE_RETURN, -1));
}
