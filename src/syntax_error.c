/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:56:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 14:42:40 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static int	syntax_error(char *error_message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\'\n", 2);
	return (258);
}

static int	check_tokens(t_token *token, int type, t_list *lst)
{
	t_token	*aux;

	if (type >= 0 && type < 5 && token->type >= 0 && token->type < 5)
	{
		if (token->type > 0 && lst->next)
		{
			lst = lst->next;
			aux = lst->content;
			if (type == 0 && aux->type < 0)
				return (0);
		}
		return (syntax_error(token->string));
	}
	if (!token->string || (type == 4 && !token->type))
	{
		if (type > 0 && type < 5)
			return (syntax_error("newline"));
		else if (type == 0)
			return (syntax_error("|"));
	}
	return (0);
}

static int	check_quotes(char *str)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while (str[i])
		state = quote_state(state, str[i++]);
	if (state == 1)
		return (syntax_error("\'"));
	else if (state == 2)
		return (syntax_error("\""));
	return (0);
}

int	syntax_error_check(t_list *lst)
{
	t_token	*token;
	int		type;
	int		error;
	int		state;

	token = lst->content;
	if (token->type == PIPE)
		return (syntax_error(token->string));
	state = 0;
	error = 0;
	while (token->string && !error)
	{
		if (ft_strchr(token->string, '\'') || ft_strchr(token->string, '\"'))
			error = check_quotes(token->string);
		type = token->type;
		lst = lst->next;
		token = lst->content;
		if (!error)
			error = check_tokens(token, type, lst);
	}
	return (error);
}
