/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:04:04 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/14 11:32:22 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static int	get_token_type(char	*str)
{
	if (ft_strchr(str, '|'))
		if (!ft_strncmp(str, "|\0", 2))
			return (PIPE);
	if (ft_strchr(str, '<'))
	{
		if ((!ft_strncmp(str, "<\0", 2))
			|| (str[0] == '<' && str[1] && str[1] != '<'))
			return (INFILE);
		else if (!ft_strncmp(str, "<<\0", 3)
			|| (str[0] == '<' && str[1] == '<' && str[2]))
			return (HERE_DOC);
	}
	else if (ft_strchr(str, '>'))
	{
		if (!ft_strncmp(str, ">\0", 2)
			|| (str[0] == '>' && str[1] && str[1] != '>'))
			return (TRUNC);
		else if (!ft_strncmp(str, ">>\0", 3)
			|| (str[0] == '>' && str[1] == '>' && str[2]))
			return (APPEND);
	}
	return (-1);
}

t_list	*set_type(t_list **token_list)
{
	t_list	*tmp_lst;
	t_token	*aux;

	tmp_lst = *token_list;
	aux = tmp_lst->content;
	while (aux->string)
	{
		if (aux->type < 0)
			aux->type = get_token_type(aux->string);
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
	}
	return (*token_list);
}
