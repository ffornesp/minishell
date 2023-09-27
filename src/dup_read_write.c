/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_read_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:52:35 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 14:17:23 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static int	get_last_redirect_type(t_list *lst, int type1, int type2)
{
	t_token	*token;
	int		out;

	out = 0;
	while (lst->next)
	{
		token = lst->content;
		if (token->type == PIPE)
			break ;
		if (token->type == type1 || token->type == type2)
			out = token->type;
		lst = lst->next;
	}
	return (out);
}

static int	dup_hdoc(t_list *lst, t_data *data)
{
	t_token	*token;
	int		count;

	count = 0;
	while (lst)
	{
		token = lst->content;
		if (!token->string)
			break ;
		if (token->type == PIPE)
			break ;
		else if (token->type == HERE_DOC)
			count++;
		lst = lst->next;
	}
	count += data->hd_count - 1;
	if (dup2(data->hdoc_fds[count], STDIN_FILENO) == -1)
		return (1);
	return (0);
}

int	dup_read(t_list *lst, t_data *data)
{
	int		fd;
	char	*input;

	input = NULL;
	fd = 0;
	if (p_type_count(lst, INFILE) || p_type_count(lst, HERE_DOC))
	{
		if (find_input(lst, &input, INFILE, HERE_DOC))
			return (126);
	}
	else
		return (0);
	if (input && get_last_redirect_type(lst, INFILE, HERE_DOC) == INFILE)
	{
		fd = open(input, O_RDONLY, 0666);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
		close(fd);
	}
	else
		return (dup_hdoc(lst, data));
	return (0);
}

int	dup_write(t_list *lst)
{
	int		fd;
	char	*output;

	output = NULL;
	fd = 0;
	if (p_type_count(lst, TRUNC) || p_type_count(lst, APPEND))
		find_input(lst, &output, TRUNC, APPEND);
	else
		return (0);
	if (output)
	{
		create_files(lst);
		if (get_last_redirect_type(lst, TRUNC, APPEND) == APPEND)
			fd = open(output, O_CREAT | O_APPEND | O_WRONLY, 0666);
		else
			fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1);
		close(fd);
	}
	return (0);
}
