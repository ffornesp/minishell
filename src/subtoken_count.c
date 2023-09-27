/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:22:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/05 16:33:54 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static int	count_subtokens_utils(char *string)
{
	int	state;
	int	quotes;
	int	count;
	int	i;

	state = 0;
	quotes = 0;
	count = 0;
	i = -1;
	while (string[++i])
	{
		state = quote_state(state, string[i]);
		if (!state && !count && string[i] != '\'' && string[i] != '\"')
		{
			quotes++;
			count = 1;
		}
		else if (state)
			count = 0;
		if (state == 1 && string[i] == '\'')
			quotes++;
		else if (state == 2 && string[i] == '\"')
			quotes++;
	}
	return (quotes);
}

int	count_subtokens(char *string)
{
	int	count;

	if (!ft_strchr(string, '\'') && !ft_strchr(string, '\"'))
		return (0);
	count = count_subtokens_utils(string);
	if (count > 1)
		return (count);
	return (0);
}
