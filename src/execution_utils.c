/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:36:06 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/28 10:56:57 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int	child_exec(t_list *lst, t_list **env_lst, char **env)
{
	int		err;

	err = builtin_check(lst, env_lst, env);
	if (err >= 0)
		return (err);
	return (exec_commands(lst, env));
}

static void	exec_utils(t_list *lst, t_list **env_lst, t_data *data, char **env)
{
	int		err;
	t_token	*token;

	token = lst->content;
	err = dup_read(lst, data);
	if (err)
		exit(err);
	else if (data->read_pipe_fds >= 0)
	{
		if (!p_type_count(lst, INFILE) && !p_type_count(lst, HERE_DOC))
			if (dup2(data->read_pipe_fds, STDIN_FILENO) < 0)
				exit(1);
		close(data->read_pipe_fds);
	}
	if (dup_write(lst))
		exit(1);
	else if (type_count(lst, PIPE) && !check_redirect(lst, TRUNC, APPEND))
	{
		if (dup2(data->write_pipe_fds[1], STDOUT_FILENO) < 0)
			exit(1);
		close(data->write_pipe_fds[0]);
		close(data->write_pipe_fds[1]);
	}
	err = child_exec(lst, env_lst, env);
	exit(err);
}

int	gen_child(t_list *lst, t_list **env_lst, t_data *data, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		exec_utils(lst, env_lst, data, env);
	return (pid);
}

int	get_child_status(int pid, t_data *data)
{
	int	status;

	while (data->process_id--)
	{
		if (pid == waitpid(0, &status, 0))
		{
			if (WIFEXITED(status))
				set_or_return_exit_status(MODE_SET, WEXITSTATUS(status));
			else
				set_or_return_exit_status(MODE_SET, 0);
			if (WTERMSIG(status) == SIGINT)
				return (set_or_return_exit_status(MODE_SET, 130));
			else if (WTERMSIG(status) == SIGQUIT)
			{
				ft_putstr_fd("Quit: 3\n", 0);
				return (set_or_return_exit_status(MODE_SET, 131));
			}
		}
	}
	return (0);
}
