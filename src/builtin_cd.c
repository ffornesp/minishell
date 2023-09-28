/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:05:30 by laugarci          #+#    #+#             */
/*   Updated: 2023/09/28 15:54:49 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"
#include "libft_bonus.h"
#include "parser.h"

static int	error_cd(char *filename, char *message, int value)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(message, 2);
	return (value);
}

static char	*get_env_var(char *key, t_list **env_lst)
{
	t_env	*var;
	t_list	*lst;

	lst = *env_lst;
	while (lst->next)
	{
		var = lst->content;
		if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
			return ((var->value + 1));
		lst = lst->next;
	}
	return (NULL);
}

static int	go_home(t_list **env_lst)
{
	if (chdir(get_env_var("HOME", env_lst)))
		return (1);
	return (0);
}

int	builtin_cd(t_list *lst, t_list **env_lst)
{
	t_token	*token;
	t_list	*tmp;

	tmp = lst->next;
	token = tmp->content;
	if (count_list(lst) == 2)
		return (go_home(env_lst));
	else if (!ft_strchr(token->string, '/') && ft_strlen(token->string) >= 256)
		return (error_cd(token->string, ": File name too long\n", 1));
	else if (access((token->string), F_OK) != -1)
	{
		if (access((token->string), R_OK) != -1)
		{
			if (chdir(token->string) == -1)
				return (error_cd(token->string, ": Not a directory\n", 1));
		}
		else
			return (error_cd(token->string, ": Permission denied\n", 1));
	}
	else if (*token->string)
		return (error_cd(token->string, ": No such file or directory\n", 1));
	return (0);
}
