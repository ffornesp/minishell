/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:09:20 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/27 14:23:46 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "parser.h"
#include "libft_bonus.h"
#include <unistd.h>
#include <stdio.h>

char	*find_command(t_list *lst)
{
	size_t	total_length;
	t_token	*token;
	int		i;
	char	*result;

	total_length = total_input_len(lst);
	result = malloc(sizeof(char) * (total_length + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (lst->next)
	{
		token = lst->content;
		if (token->type >= 0)
			break ;
		if (i > 0)
			result[i++] = ' ';
		ft_strlcpy(result + i, token->string, total_length);
		i += ft_strlen(token->string);
		lst = lst->next;
	}
	result[total_length] = '\0';
	return (result);
}

static int	access_check(t_token *token)
{
	if (token->type == INFILE)
	{
		if (access(token->string, F_OK))
			return (error_exec(token->string, \
					"No such file or directory\n", 1));
		else if (access(token->string, R_OK))
			return (error_exec(token->string, \
					"Permission denied\n", 1));
	}
	else if (token->type == TRUNC || token->type == APPEND)
	{
		if (!access(token->string, F_OK))
		{
			if (access(token->string, W_OK))
				return (error_exec(token->string, "Permission denied\n", 1));
		}
	}
	return (0);
}

int	find_input(t_list *lst, char **dst, int type1, int type2)
{
	t_token	*token;
	int		err;

	token = lst->content;
	err = 0;
	while (lst)
	{
		if (token->type == PIPE || !token->string)
			break ;
		if (token->type == type1 || token->type == type2)
		{
			*dst = token->string;
			err = access_check(token);
			if (err)
				return (err);
		}
		lst = lst->next;
		token = lst->content;
	}
	return (0);
}
