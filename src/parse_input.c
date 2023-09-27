/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:29:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/26 14:27:01 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "parser.h"

static int	free_list_and_return(t_list *lst, int exit_status)
{
	ft_lstclear(&lst, (void *)free_token);
	return (exit_status);
}

static int	is_empty(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	parse_input(char *str, char *envp[], t_list **token_list)
{
	t_list	*lst;
	int		flag;
	int		error;

	if (is_empty(str))
		return (1);
	flag = 0;
	if (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>'))
	{
		str = clean_input(str);
		if (!str)
			return (print_error_and_return("Cannot allocate memory\n", 12));
		flag = 1;
	}
	lst = save_tokens(str);
	if (flag)
		free(str);
	if (!lst)
		return (print_error_and_return("Cannot allocate memory\n", 12));
	error = process_tokens(&lst, envp);
	if (error)
		return (free_list_and_return(lst, error));
	*token_list = lst;
	return (0);
}
