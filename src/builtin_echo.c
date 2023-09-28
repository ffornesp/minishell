/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:30:35 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/27 19:13:55 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"

int	count_flags(t_list *lst)
{
	int		flag;
	t_token	*token;
	size_t	i;

	token = lst->content;
	flag = 0;
	while (lst->next)
	{
		i = 1;
		if (token->string[0] == '-' && token->string[1] == 'n')
		{
			while (token->string[i] == 'n')
				i++;
			if (i == ft_strlen(token->string))
				flag++;
			else
				break ;
		}
		lst = lst->next;
		token = lst->content;
	}
	return (flag);
}

t_list	*move_list(t_list *aux, int flag)
{
	t_token	*token;

	token = aux->content;
	while (flag > 0)
	{
		aux = aux->next;
		flag--;
	}
	return (aux);
}

void	print_echo(t_list *aux, int flag)
{
	t_token	*token;
	int		i;

	i = 0;
	token = aux->content;
	while (aux->next)
	{
		if (token->type != -1)
			break ;
		if (i > 0)
			printf(" ");
		printf("%s", token->string);
		i++;
		aux = aux->next;
		token = aux->content;
	}
	if (flag == 0)
		printf("\n");
}

int	builtin_echo(t_list *lst)
{
	t_token	*token;
	t_list	*aux;
	int		i;
	int		flag;

	aux = lst;
	flag = 0;
	i = count_list(lst);
	if (i == 2)
	{
		printf("\n");
		return (0);
	}
	aux = aux->next;
	token = aux->content;
	if (ft_strncmp(token->string, "-n", 2) == 0)
		flag = count_flags(lst);
	aux = move_list(aux, flag);
	print_echo(aux, flag);
	return (0);
}
