/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:05:35 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/27 16:10:35 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"
#include <limits.h>
#include <stdlib.h>

void	put_numeric_error(char *input)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static int	check_digits_utils(char *input)
{
	int	i;

	i = 0;
	while (ft_isdigit(*input))
	{
		i++;
		input++;
		if (i > 20)
			put_numeric_error(input - i);
	}
	while (*input == ' ')
		input++;
	if (*input && !ft_isdigit(*input))
		return (1);
	return (0);
}

int	check_digits(char *input)
{
	while (*input == ' ')
		input++;
	if (!ft_strncmp(input, "-18446744073709551617\0", 22))
		put_numeric_error(input);
	if (*input == '-' || *input == '+')
		input++;
	if (!input || !*input)
		return (1);
	while (*input == '0')
		input++;
	if (!input || !*input)
	{
		ft_putstr_fd("exit\n", 0);
		exit(0);
	}
	return (check_digits_utils(input));
}
