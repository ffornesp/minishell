/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:29:17 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/27 20:00:32 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "libft_bonus.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

static char	*find_delimiter(t_list *lst, int id, int *flag)
{
	t_token	*token;
	int		i;

	i = 0;
	token = lst->content;
	id++;
	while (lst && i < id)
	{
		if (!token || !token->string)
			return (NULL);
		if (token->type == HERE_DOC)
			i++;
		if (i == id)
			break ;
		lst = lst->next;
		token = lst->content;
	}
	if (token->quotes)
		*flag = 1;
	return (token->string);
}

static int	input_heredoc_util(char *input, int *fds, int flag, char **env)
{
	char	*aux;

	aux = input;
	if (!flag)
	{
		input = expand_evals(input, env);
		if (!input)
		{
			free(aux);
			return (12);
		}
	}
	write(fds[1], input, ft_strlen(input));
	free(input);
	close(fds[1]);
	close(fds[0]);
	return (0);
}

static int	input_heredoc(char *del, int *fds, int flag, char **env)
{
	char	*aux;
	char	*input;
	char	*text;

	text = NULL;
	while (42)
	{
		input = readline("> ");
		if (ft_strncmp(input, del, ft_strlen(del) + 1) == 0)
			break ;
		text = ft_strjoin(text, input);
		free(input);
		if (!text)
			return (12);
		aux = text;
		text = ft_strjoin(text, "\n");
		free(aux);
		if (!text)
			return (12);
	}
	if (input_heredoc_util(text, fds, flag, env))
		return (12);
	return (0);
}

static void	check_signal(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	set_or_return_exit_status(MODE_SET, WEXITSTATUS(status));
}

int	here_doc(t_list *lst, int id, char **env)
{
	char	*del;
	int		fds[2];
	int		pid;
	int		flag;

	flag = 0;
	del = find_delimiter(lst, id, &flag);
	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		signal_setup(STATE_HDOC);
		if (input_heredoc(del, fds, flag, env))
			exit(12);
		exit(0);
	}
	close(fds[1]);
	check_signal(pid);
	return (fds[0]);
}
