/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:13:09 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/19 18:13:32 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

int	exec_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
	return (0);
}
