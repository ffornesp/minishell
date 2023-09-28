/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:52:54 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 17:49:56 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include <stdlib.h>

void	builtin_exit(char *input)
{
	long long	out;

	if (!input)
		exit(0);
	out = ft_atoll(input);
	if (check_digits(input) || (!out && *input != '\0'))
		put_numeric_error(input);
	if (out > 0)
		while (out > 255)
			out -= (out / 255) * 256;
	else if (out < 0)
	{
		while (out < -255)
			out += (out / 255) * 256 * -1;
		if (out == -1)
			out = 255;
		else
			out -= 2;
	}
	ft_putstr_fd("exit\n", 0);
	exit(out);
}

static void	char_is_null(void)
{
	ft_putstr_fd("exit\n", 0);
	ft_putstr_fd("minishell: exit: : numeric argument required\n", 2);
	builtin_exit("255");
}

static int	too_many_args(int *err)
{
	ft_putstr_fd("exit\n", 0);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	set_or_return_exit_status(MODE_SET, 1);
	*err = 1;
	return (1);
}

void	exit_check(t_list *lst, int *err, t_token *token)
{
	t_token	*aux;

	if (!ft_strncmp(token->string, "exit\0", 5))
	{
		lst = lst->next;
		token = lst->content;
		if (token->string && *token->string)
		{
			lst = lst->next;
			aux = lst->content;
			if (aux->string && aux->type < 0)
			{
				if (!ft_isdigit(*token->string))
					builtin_exit(token->string);
				else if (too_many_args(err))
					return ;
			}
			else
				builtin_exit(token->string);
		}
		else if (token->string && !*token->string)
			char_is_null();
		builtin_exit(ft_itoa(set_or_return_exit_status(MODE_RETURN, -1)));
	}
}
