/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:43:15 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/26 10:40:28 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_defs.h"
#include <stdlib.h>

int	free_key_and_return(t_env *var)
{
	if (var->key)
		free(var->key);
	free(var);
	return (0);
}

t_env	*export_set_value(t_env *env_var, t_env *var, char *str)
{
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	while (str[j] && str[j] != '=')
		j++;
	if (str[j])
		if (j)
			if (str[j - 1] == '+')
				flag = 1;
	if (flag)
	{
		env_var->value = ft_strjoin(env_var->value, ++var->value);
		if (!env_var->value)
			return (NULL);
	}
	else
	{
		env_var->value = ft_strdup(var->value);
		if (!env_var->value)
			return (NULL);
	}
	return (env_var);
}
