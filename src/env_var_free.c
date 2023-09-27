/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:46:10 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/22 19:42:30 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_defs.h"

void	free_var(t_env *var)
{
	if (var)
	{
		if (var->key)
			free(var->key);
		if (var->value)
			free(var->value);
		free(var);
	}
	return ;
}

int	free_var_return_value(t_env *var, int value)
{
	free_var(var);
	return (value);
}
