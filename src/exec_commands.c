/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:04:45 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/27 16:03:28 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "libft_bonus.h"
#include "parser.h"

static int	count_command(t_list *lst)
{
	t_token	*token;
	int		i;

	token = lst->content;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
		token = lst->content;
		if (!token->string || token->type >= 0)
			break ;
	}
	return (i);
}

static char	**allocate_cmd(int size)
{
	char	**dst;

	dst = malloc(sizeof(char *) * (size + 1));
	if (!dst)
	{
		print_error_and_return("Cannot allocate memory\n", 12);
		return (NULL);
	}
	return (dst);
}

static char	**full_cmd(t_list *lst, char **env)
{
	int		i;
	int		j;
	char	**dst;
	t_token	*token;

	i = count_command(lst);
	dst = allocate_cmd(i);
	token = lst->content;
	get_path(token->string, env, dst);
	if (!dst || !dst[0])
	{
		free(dst);
		return (NULL);
	}
	j = 1;
	lst = lst->next;
	while (j < i)
	{
		token = lst->content;
		dst[j++] = token->string;
		lst = lst->next;
	}
	dst[j] = NULL;
	return (dst);
}

int	exec_commands(t_list *lst, char **env)
{
	char	**cmd;
	t_token	*token;

	token = lst->content;
	if (token->type != -1)
		return (0);
	cmd = full_cmd(lst, env);
	if (!cmd)
		return (set_or_return_exit_status(MODE_RETURN, -1));
	if (access(cmd[0], F_OK))
		return (set_or_return_exit_status(MODE_SET, 127));
	if ((execve(cmd[0], cmd, env)) == -1)
	{
		if (ft_strchr(cmd[0], '/'))
		{
			error_exec(cmd[0], "is a directory\n", 126);
			free(cmd[0]);
			free(cmd);
			exit(126);
		}
		return (1);
	}
	return (0);
}
