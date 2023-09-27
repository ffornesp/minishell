/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:39:50 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 11:33:54 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "minishell_defs.h"
#include "parser.h"

int	invalid_identifier(char *builtin, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	set_or_return_exit_status(MODE_SET, 1);
	return (0);
}

int	print_error_builtin(char *builtin, char *error_message, int value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(error_message, 2);
	set_or_return_exit_status(MODE_SET, value);
	return (value);
}

int	error_exec(char *command, char *error_message, int value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_message, 2);
	set_or_return_exit_status(MODE_SET, value);
	return (value);
}

int	print_error_and_return(char *error_message, int value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_message, 2);
	set_or_return_exit_status(MODE_SET, value);
	return (value);
}
