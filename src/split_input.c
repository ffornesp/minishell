/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:35:07 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 15:12:11 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static char	*save_it(char *input, int start, int end)
{
	char	*out;

	if (start)
		input += start;
	if (!ft_strncmp(input, "~ ", 2) || !ft_strncmp(input, "~\0", 2))
		return (ft_strdup("$HOME"));
	else if (!ft_strncmp(input, "~/", 2))
		return (ft_strjoin("$HOME", (input + 1)));
	out = malloc(sizeof(char) * (end + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, input, end + 1);
	return (out);
}

static char	*get_string(char *input, int number, int i, int j)
{
	int		open;
	int		counted;
	int		count;

	open = 0;
	counted = 0;
	count = 0;
	while (input[++i])
	{
		open = quote_state(open, input[i]);
		if (!open && input[i] == ' ')
			counted = 0;
		else
		{
			if (!counted)
				count++;
			if (count == number)
				j++;
			counted = 1;
		}
		if ((count != number && j)
			|| (count == number && !open && input[i] == ' ' && j))
			break ;
	}
	return (save_it(input, (i - j), j));
}

static char	**save_new_input(char *input, int amount)
{
	char	**out;
	int		i;

	out = malloc(sizeof(char *) * (amount + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		out[i] = get_string(input, (i + 1), -1, 0);
		if (!out[i])
			return (free_double((void **)out));
		i++;
	}
	out[i] = NULL;
	return (out);
}

static char	**charp_to_charpp(char *input)
{
	char	**out;
	char	*aux;

	out = malloc(sizeof(char *) * 2);
	if (!out)
		return (NULL);
	if (!ft_strncmp(input, "~\0", 2))
		input = "$HOME";
	out[0] = ft_strtrim(input, " ");
	if (out[0] && ft_strchr(out[0], '\t'))
	{
		aux = out[0];
		out[0] = ft_strtrim(out[0], "\t");
		free(aux);
	}
	if (!out[0])
	{
		free(out);
		return (NULL);
	}
	out[1] = NULL;
	return (out);
}

char	**split_input(char *input)
{
	int		i;
	int		j;
	int		open;
	int		counted;

	i = 0;
	j = 0;
	open = 0;
	counted = 0;
	while (input[i])
	{
		open = quote_state(open, input[i]);
		if (input[i++] == ' ' && !open)
			counted = 0;
		else if (!counted)
		{
			j++;
			counted = 1;
		}
	}
	if (j == 1)
		return (charp_to_charpp(input));
	return (save_new_input(input, j));
}
