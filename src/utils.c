/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:26:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/24 17:17:04 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser.h"
#include "libft_bonus.h"

#include <stdio.h>

int	type_count(t_list *lst, int type)
{
	t_token	*aux;
	t_list	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp->next)
	{
		aux = tmp->content;
		if (aux->type == type)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	p_type_count(t_list *lst, int type)
{
	int		c;
	t_list	*tmp;
	t_token	*aux;

	c = 0;
	tmp = lst;
	while (tmp->next)
	{
		aux = tmp->content;
		if (type != PIPE)
			if (aux->type == PIPE)
				break ;
		if (aux->type == type)
			c++;
		tmp = tmp->next;
	}
	return (c);
}

int	total_input_len(t_list *lst)
{
	t_list	*current;
	t_token	*token;
	int		total_length;

	current = lst;
	total_length = 0;
	while (current->next)
	{
		token = current->content;
		total_length += ft_strlen(token->string);
		current = current->next;
	}
	total_length = total_length + (count_list(lst));
	return (total_length);
}

char	*cpy_list(t_list *lst)
{
	t_token	*token;
	char	*cmd;

	cmd = NULL;
	token = lst->content;
	while (lst)
	{
		if (token->type != -1)
			break ;
		cmd = ft_strjoin(cmd, token->string);
		lst = lst->next;
		token = lst->content;
	}
	return (cmd);
}

int	count_list(t_list *lst)
{
	int		i;
	t_list	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
