/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:28:23 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/15 11:31:17 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*util_util_lol(char *tmp, char *input, char *aux, int i)
{
	if (input[i])
	{
		tmp = ft_strjoin(tmp, (input + i));
		free(aux);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

static char	*update_input_util(int i, char *tmp, char *str, char *input)
{
	char	*aux;

	aux = tmp;
	if (!str)
		str = "";
	tmp = ft_strjoin(tmp, str);
	free(aux);
	if (!tmp)
		return (NULL);
	aux = tmp;
	while (input[i] && ((i && input[i - 1] == '$'
				&& (ft_isalpha(input[i]) || input[i] == '_' || input[i] == '?'))
			|| (ft_isalnum(input[i]) || input[i] == '_')))
	{
		i++;
		if (input[i - 1] == '?')
			break ;
	}
	return (util_util_lol(tmp, input, aux, i));
}

char	*update_input(char *input, char *str)
{
	int		i;
	char	*tmp;
	char	*aux;

	i = 0;
	while (input[i])
		if (input[i++] == '$')
			if (ft_isalpha(input[i]) || input[i] == '_'
				|| (input[i - 1] == '$' && input[i] == '?'))
				break ;
	if (i > 1)
		tmp = malloc(sizeof(char) * i);
	else
		tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	if (i > 1)
		ft_strlcpy(tmp, input, i);
	aux = str;
	tmp = update_input_util(i, tmp, str, input);
	free(str);
	return (tmp);
}
