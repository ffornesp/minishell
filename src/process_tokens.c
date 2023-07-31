/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:15:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/31 17:32:55 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include "libft_bonus.h"
#include <stdlib.h>
#include <stdio.h>

static int	get_token_type(char	*str)
{
	if (!ft_strncmp(str, "|\0", 2))
		return (PIPE);
	else if (!ft_strncmp(str, "<\0", 2))
		return (INFILE);
	else if (!ft_strncmp(str, "<<\0", 3))
		return (HERE_DOC);
	else if (!ft_strncmp(str, ">\0", 2))
		return (O_TRUNC);
	else if (!ft_strncmp(str, ">>\0", 3))
		return (O_APPEND);
	return (-1);
}

void	process_tokens(t_list **token_list)
{
	t_list	*tmp_lst;
	t_token	*aux;
	t_token	*tmp;

	tmp_lst = *token_list;
	aux = tmp_lst->content;
	while (1)
	{
		if (aux->type < 0)
		{
			aux->type = get_token_type(aux->string);
			if (aux->type > 0)
			{
				tmp_lst = tmp_lst->next;
				tmp = tmp_lst->content;
				tmp->type = aux->type;
			}
		}
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
		if (!aux->string)
			break ;
	}
}
