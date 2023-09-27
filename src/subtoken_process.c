/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:45:48 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 14:52:16 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"
#include "libft_bonus.h"
#include <stdlib.h>
#include <stdio.h>

static int	set_strings(char *str, char **dst)
{
	int	state;
	int	i;
	int	j;

	i = 0;
	j = 0;
	state = 0;
	while (str[i])
	{
		state = quote_state(state, str[i]);
		if ((!state && (str[i] == '\'' || str[i] == '\"'))
			|| (!state && (str[i + 1] == '\''
					|| str[i + 1] == '\"' || str[i + 1] == '\0')))
		{
			dst[j] = ft_calloc(sizeof(char), (i + 2));
			if (!dst[j])
				return (free_double_and_return((void **)dst, 12));
			ft_strlcpy(dst[j++], str, (i + 2));
			str = str + i + 1;
			i = -1;
		}
		i++;
	}
	return (0);
}

static t_list	*add_subtokens(t_list **list, char **strings)
{
	t_list	*new_list;
	t_token	*token;
	int		i;
	int		type;

	i = 0;
	type = 5;
	new_list = *list;
	token = new_list->content;
	free(token->string);
	token->string = strings[i];
	token->type = type;
	new_list = NULL;
	while (strings[++i])
	{
		if (!strings[i + 1])
			type = 6;
		ft_lstadd_back(&new_list, ft_lstnew(new_token(strings[i], type, -1)));
	}
	((t_list *)*list)->next = new_list;
	return (*list);
}

static int	generate_subtokens(t_list **list, int count)
{
	t_list	*new_list;
	t_list	*aux;
	t_token	*token;
	char	**strings;

	new_list = *list;
	strings = ft_calloc(sizeof(char *), (count + 1));
	if (!strings)
		return (12);
	token = new_list->content;
	if (set_strings(token->string, strings))
		return (12);
	aux = new_list->next;
	new_list = add_subtokens(&new_list, strings);
	free(strings);
	ft_lstadd_back(&new_list, aux);
	*list = new_list;
	return (0);
}

int	process_subtokens(t_list **token_list)
{
	t_list	*aux;
	t_token	*token;
	int		subtoken_count;

	aux = *token_list;
	while (42)
	{
		token = aux->content;
		if (token->type < 0)
		{
			subtoken_count = count_subtokens(token->string);
			if (subtoken_count)
				if (generate_subtokens(&aux, subtoken_count))
					return (12);
		}
		aux = aux->next;
		token = aux->content;
		if (!token->string)
			break ;
	}
	return (0);
}
