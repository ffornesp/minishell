/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:04:51 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/14 15:50:53 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

// Trims the recieved input in order to return only the name of the evironment 
// 	value without any other stuff next to it.
// Useful in cases where two evals are next to each other or other stuff is.
// 		ex:	$USER$USER     $USER.hola
static char	*true_eval(char *str)
{
	int		i;
	char	*out;

	i = 0;
	if (!ft_strncmp(str, "$?\0", 3))
	{
		out = ft_strdup("?");
		if (!out)
			return (NULL);
		return (out);
	}
	while (str[i])
	{
		if (((!i && !ft_isalpha(str[i]))
				|| !ft_isalnum(str[i])) && str[i] != '_')
			break ;
		i++;
	}
	if (!str[i])
		return (ft_strdup(str));
	out = malloc(sizeof(char) * (i + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, str, (i + 1));
	return (out);
}

// Finds in the environment recieved, the value of the eval 'str' and returns
// 		it.
int	find_eval(char *str, char *envp[], char **dst)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	str = true_eval(str);
	if (!str)
		return (1);
	j = ft_strlen(str);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
			if (envp[i][j] == '=')
				break ;
		i++;
	}
	if (envp[i])
	{
		out = ft_strchr(envp[i], '=');
		*dst = (out + 1);
	}
	else
		*dst = NULL;
	free(str);
	return (0);
}

// Returns the amount of expansions found in a string
int	expansion_amount(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
			j++;
		else if (input[i] == '$' && (ft_isalpha(input[i + 1])
				|| input[i + 1] == '_'))
			j++;
		i++;
	}
	return (j);
}
