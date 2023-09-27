/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:07:29 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/26 23:55:47 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

t_list	*move_to_pipe(t_list *lst)
{
	t_token	*token;
	t_list	*aux;

	aux = lst;
	token = lst->content;
	while (token->type != PIPE)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
		token = lst->content;
	}
	if (token->type == PIPE)
		return (lst->next);
	return (aux);
}

int	check_redirect(t_list *lst, int type1, int type2)
{
	t_token	*token;
	int		i;

	i = 0;
	token = lst->content;
	while (lst)
	{
		if (!lst->next)
			break ;
		if (token->type == type1 || token->type == type2)
			i++;
		if (token->type == PIPE)
			break ;
		lst = lst->next;
		token = lst->content;
	}
	if (i > 0)
		return (1);
	return (0);
}

void	create_files(t_list *lst)
{
	int		fd;
	t_token	*token;

	token = lst->content;
	while (lst->next)
	{
		token = lst->content;
		if (token->type == PIPE)
			break ;
		if (token->type == APPEND)
		{
			fd = open(token->string, O_WRONLY | O_CREAT | O_APPEND, 0666);
			close(fd);
		}
		else if (token->type == TRUNC)
		{
			fd = open(token->string, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			close(fd);
		}
		lst = lst->next;
	}
}
