/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:24:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/13 18:42:21 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

#include <unistd.h>
#include <stdio.h>

t_list	*process_list(t_list *lst, int process_id)
{
	t_token	*token;
	t_list	*aux;
	int		count;

	if (process_id == 0)
		return (lst);
	aux = lst;
	token = aux->content;
	count = 0;
	while (count < process_id)
	{
		if (token->type == PIPE)
			count++;
		aux = aux->next;
		token = aux->content;
		if (!token->string)
			return (NULL);
	}
	return (aux);
}
