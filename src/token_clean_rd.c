/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clean_rd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:17:33 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/27 16:18:39 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	clean_redirects(t_list **lst)
{
	t_list	*tmp_lst;
	t_token	*token;
	char	*str;
	int		next;

	tmp_lst = *lst;
	token = tmp_lst->content;
	next = 0;
	while (token->string)
	{
		str = token->string;
		if (token->type > 0)
		{
			if (!ft_strncmp(str, "<\0", 2) || !ft_strncmp(str, "<<\0", 3)
				|| !ft_strncmp(str, ">\0", 2) || !ft_strncmp(str, ">>\0", 3))
				next = token->type;
			else
				next = 0;
		}
		tmp_lst = tmp_lst->next;
		token = tmp_lst->content;
		if (next)
			token->type = next;
	}
}
