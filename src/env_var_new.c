/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:45:08 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/24 19:03:23 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include <stdlib.h>
#include <stdio.h>

static void	*free_and_return_envar(t_env *var)
{
	free_var(var);
	return (NULL);
}

static char	*new_var_utils(char *input, int *n, int *add)
{
	char	*out;
	int		i;

	i = 0;
	while (input[i] && input[i] != '=')
		i++;
	if (i && input[i - 1] == '+')
	{
		*add = 1;
		i--;
	}
	*n = i;
	out = malloc(sizeof(char) * (i + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, input, i + 1);
	return (out);
}

t_env	*new_env_var(char *input)
{
	int		i;
	int		add;
	t_env	*out;

	i = 0;
	add = 0;
	out = malloc(sizeof(t_env));
	if (!out)
		return (NULL);
	out->key = new_var_utils(input, &i, &add);
	if (!out->key)
		return (free_and_return_envar(out));
	input += i;
	if (add)
		input += 1;
	if (input && *input)
	{
		out->value = malloc(sizeof(char) * ft_strlen(input) + 1);
		if (!out->value)
			return (free_and_return_envar(out));
		ft_strlcpy(out->value, input, ft_strlen(input) + 1);
	}
	else
		out->value = NULL;
	return (out);
}
