/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:48:00 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/15 11:12:14 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	check_pipes(char *str, int i)
{
	if (i && str[i - 1] != ' ')
		return (i);
	else if (str[i + 1] && str[i + 1] != ' ')
		return (i + 1);
	return (0);
}

static int	check_redirections(char *str, int i)
{
	if (i > 0 && str[i - 1] != ' ' && str[i - 1] != str[i])
		return (i);
	if (str[i + 1] && str[i + 1] != str[i] && str[i + 1] != ' ')
		return (i + 1);
	else if (str[i + 1] && str[i + 1] == str[i] && str[i + 2]
		&& str[i + 2] != ' ')
		return (i + 2);
	return (0);
}

int	needs_space(char *str)
{
	int	i;
	int	out;
	int	open;

	if (!str)
		return (0);
	i = 0;
	out = 0;
	open = 0;
	while (str[i])
	{
		open = quote_state(open, str[i]);
		if (!open)
		{
			if (str[i] == '|')
				out += check_pipes(str, i);
			else if (str[i] == '<' || str[i] == '>')
				out = check_redirections(str, i);
		}
		if (out != 0)
			return (out);
		i++;
	}
	return (0);
}
