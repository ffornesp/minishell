/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:53:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/15 11:08:32 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

static char	*allocate_new_input(char *out, char *str, int i)
{
	char	*aux;
	char	*remains;

	aux = out;
	remains = str + i;
	remains = ft_strjoin(" ", remains);
	if (!remains)
		return (NULL);
	aux = ft_strjoin(aux, remains);
	free(remains);
	if (!aux)
		return (NULL);
	return (aux);
}

static char	*rewrite_input(char *str, int i)
{
	char	*out;
	char	*aux;

	out = malloc(sizeof(char) * i + 1);
	if (!out)
		return (NULL);
	ft_strlcpy(out, str, i + 1);
	aux = out;
	out = allocate_new_input(out, str, i);
	free(aux);
	if (!out)
		return (NULL);
	return (out);
}

static char	*first_pos_re(char *str)
{
	if (str[0] == '<' && str[1] != '<' && str[1] != ' ' && str[1])
		return (ft_strjoin("< ", (str + 1)));
	else if (str[0] == '<' && str[1] == '<' && str[2] != '<'
		&& str[2] != ' ' && str[2])
		return (ft_strjoin("<< ", (str + 2)));
	if (str[0] == '>' && str[1] != '>' && str[1] != ' ' && str[1])
		return (ft_strjoin("> ", (str + 1)));
	else if (str[0] == '>' && str[1] == '>' && str[2] != '>'
		&& str[2] != ' ' && str[2])
		return (ft_strjoin(">> ", (str + 2)));
	return (ft_strdup(str));
}

char	*clean_input(char *str)
{
	int		i;
	char	*tmp;
	char	*aux;

	tmp = first_pos_re(str);
	if (!tmp)
		return (NULL);
	i = needs_space(tmp);
	while (i)
	{
		aux = tmp;
		tmp = rewrite_input(tmp, i);
		if (!tmp)
			return (NULL);
		free(aux);
		i = needs_space(tmp);
	}
	return (tmp);
}
