/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/26 19:43:38 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*expand_input_util(char *input)
{
	char	*str;

	str = ft_strchr(input, '$');
	if (!str)
		return (NULL);
	while (*(str + 1) == '$')
		str++;
	str++;
	while (*str && *str == ' ')
	{
		str = ft_strchr(str, '$');
		if (!str)
			return (NULL);
		str++;
	}
	return (str);
}

static char	*cut_aux(char *aux)
{
	int	i;

	i = 0;
	while (aux[i])
	{
		if (aux[i] == ' ')
		{
			aux[i] = '\0';
			break ;
		}
		i++;
	}
	return (aux);
}

// This function locates the environment value in the string 
// 	recieved as input, trimming the environment value leaving 
// 	only it's reference name.
// 		Ex: ' nskj $USER a' becomes 'USER'
// Then find_eval is called, which looks for the environment 
// 	value in the environment and
// 		returns the content saved in the environment value.
static char	*expand_input(char *input, char *envp[], int *flag)
{
	char	*str;
	char	*aux;

	str = expand_input_util(input);
	if (!str)
		return (NULL);
	else if (*str == '?')
		return (ft_itoa(set_or_return_exit_status(MODE_RETURN, -1)));
	aux = ft_strdup(str);
	if (!aux)
		return (NULL);
	aux = cut_aux(aux);
	*flag = find_eval(aux, envp, &str);
	free(aux);
	if (!str)
		return (NULL);
	return (ft_strdup(str));
}

void	init_expansion_util(char *input, int *amount, char **out)
{
	*amount = expansion_amount(input);
	if (*amount)
		*out = ft_strdup("");
}

char	*expand_evals(char *input, char *envp[])
{
	int		amount;
	char	*aux;
	char	*out;
	int		flag;

	flag = 0;
	init_expansion_util(input, &amount, &out);
	if (!amount)
		return (input);
	if (!out)
		return (NULL);
	while (amount--)
	{
		aux = input;
		free(out);
		out = expand_input(input, envp, &flag);
		if (!flag)
			out = update_input(input, out);
		if (flag && !out)
			return (NULL);
		input = ft_strdup(out);
		free(aux);
	}
	free(out);
	return (input);
}
