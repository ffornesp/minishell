/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:12:15 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/16 20:29:19 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"
#include <stdlib.h>
#include <stdio.h>

static int	count_processess(t_list *lst)
{
	t_token	*token;
	int		i;

	i = 1;
	while (42)
	{
		token = lst->content;
		if (token->type == PIPE)
			i++;
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (i);
}

static void	add_to_list(t_list **aux, t_list **dst)
{
	t_list	*tmp;

	tmp = *aux;
	*aux = (t_list *)(*aux)->next;
	tmp->next = NULL;
	ft_lstadd_back(dst, tmp);
}

static void	preserve_previous_util(t_list **previous, t_list **aux)
{
	t_list	*tmp;

	tmp = *aux;
	*previous = tmp;
	*aux = tmp->next;
}

static t_list	*type_to_lst(t_list *dst, t_list **src, int type1, int type2)
{
	t_list	*aux;
	t_list	*previous;

	aux = *src;
	previous = NULL;
	while (aux->next)
	{
		if (((t_token *)(aux->content))->type == PIPE
			&& type1 != PIPE && type2 != PIPE)
			break ;
		if ((((t_token *)(aux->content))->type == type1)
			|| ((t_token *)(aux->content))->type == type2)
		{
			if (!previous)
				*src = aux->next;
			else
				previous->next = aux->next;
			add_to_list(&aux, &dst);
			if (type1 == PIPE || type2 == PIPE)
				break ;
		}
		else
			preserve_previous_util(&previous, &aux);
	}
	return (dst);
}

t_list	*organize_list(t_list *lst)
{
	t_list	*new_list;
	t_list	*tmp;
	int		count;

	count = count_processess(lst);
	new_list = NULL;
	if (!count)
		return (lst);
	while (count--)
	{
		tmp = type_to_lst(new_list, &lst, -1, -1);
		new_list = tmp;
		tmp = type_to_lst(new_list, &lst, INFILE, HERE_DOC);
		new_list = tmp;
		tmp = type_to_lst(new_list, &lst, APPEND, TRUNC);
		new_list = tmp;
		if (count > 0)
		{
			tmp = type_to_lst(new_list, &lst, PIPE, PIPE);
			new_list = tmp;
		}
	}
	ft_lstadd_back(&new_list, lst);
	return (new_list);
}
