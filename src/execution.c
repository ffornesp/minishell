/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:29:58 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/27 19:18:22 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	builtin_check(t_list *lst, t_list **env_lst, char **env)
{
	t_token	*token;
	int		err;

	err = -1;
	token = lst->content;
	exit_check(lst, &err, token);
	if (ft_strncmp(token->string, "cd\0", 3) == 0)
		err = builtin_cd(lst, env_lst);
	else if (ft_strncmp(token->string, "echo\0", 5) == 0)
		err = builtin_echo(lst);
	else if (ft_strncmp(token->string, "pwd\0", 4) == 0)
		err = builtin_pwd();
	else if (ft_strncmp(token->string, "env\0", 4) == 0)
		err = builtin_env(env);
	else if (ft_strncmp(token->string, "unset\0", 6) == 0)
		err = builtin_unset(lst, env_lst);
	else if (ft_strncmp(token->string, "export\0", 7) == 0)
		err = builtin_export(lst, env_lst);
	if (err >= 0)
	{
		set_or_return_exit_status(MODE_SET, err);
		return (err);
	}
	return (err);
}

static int	parent_exec(t_list *lst, t_list **env_lst, char **env, t_data *data)
{
	t_token	*token;
	int		err;
	int		stdio_fds[2];

	token = lst->content;
	stdio_fds[0] = dup(STDIN_FILENO);
	stdio_fds[1] = dup(STDOUT_FILENO);
	if (stdio_fds[0] == -1 || stdio_fds[1] == -1)
		return (1);
	err = dup_read(lst, data);
	if (err)
		return (err);
	err = -1;
	if (dup_write(lst))
		return (1);
	err = builtin_check(lst, env_lst, env);
	if (dup2(stdio_fds[0], STDIN_FILENO) == -1)
		return (1);
	if (dup2(stdio_fds[1], STDOUT_FILENO) == -1)
		return (1);
	close(stdio_fds[0]);
	close(stdio_fds[1]);
	return (err);
}

static t_list	*update_data(t_data *data, t_list *lst)
{
	data->process_id++;
	data->hd_count += p_type_count(lst, HERE_DOC);
	if (data->write_pipe_fds[1] > -1)
		close(data->write_pipe_fds[1]);
	if (data->read_pipe_fds >= 0)
		close(data->read_pipe_fds);
	if (data->next_read_fd >= 0)
	{
		data->read_pipe_fds = data->next_read_fd;
		data->next_read_fd = -1;
	}
	else
		data->read_pipe_fds = -1;
	lst = move_to_pipe(lst);
	return (lst);
}

int	execution(t_list *lst, t_list **env_lst, t_data *data, char **env)
{
	int	err;
	int	pid;

	err = 0;
	pid = 1;
	while (data->process_id <= data->pipe_count)
	{
		if (data->pipe_count)
		{
			pipe(data->write_pipe_fds);
			data->next_read_fd = data->write_pipe_fds[0];
		}
		else
		{
			err = parent_exec(lst, env_lst, env, data);
			if (err >= 0)
				break ;
		}
		pid = gen_child(lst, env_lst, data, env);
		lst = update_data(data, lst);
	}
	if (pid != 1)
		get_child_status(pid);
	return (err);
}
