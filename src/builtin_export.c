/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:22:49 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 11:33:47 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "minishell_defs.h"

#include <stdio.h>

static int	print_export(t_list *env_lst)
{
	t_env	*var;
	char	*str;

	while (env_lst)
	{
		var = env_lst->content;
		printf("declare -x %s", var->key);
		if (var->value)
		{
			str = var->value;
			if (*str == '=')
			{
				str++;
				if (str)
					printf("=\"%s\"", str);
				else
					printf("=\"\"");
			}
		}
		printf("\n");
		env_lst = env_lst->next;
	}
	return (0);
}

static int	add_var_to_env(t_env *var, t_list **env_lst, char *str)
{
	t_list	*lst;
	t_env	*env_var;
	char	*aux;

	lst = *env_lst;
	aux = NULL;
	while (lst)
	{
		env_var = lst->content;
		if (!ft_strncmp(env_var->key, var->key, ft_strlen(var->key) + 1))
		{
			if (!var->value)
				return (free_key_and_return(var));
			if (env_var->value)
				aux = env_var->value;
			env_var = export_set_value(env_var, var, str);
			if (aux)
				free(aux);
			return (free_key_and_return(var));
		}
		lst = lst->next;
	}
	return (1);
}

static int	is_valid_input(char *str, int i)
{
	int	flag;

	flag = 0;
	if (!str[i])
		return (invalid_identifier("export", ""));
	while (str[i])
	{
		if (!i && !ft_isalpha(str[i]) && str[i] != '_')
			flag++;
		else if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (1);
			flag++;
		}
		if (flag)
			return (invalid_identifier("export", str));
		if (str[++i] == '=')
			break ;
	}
	return (1);
}

static int	export_loop(t_token *token, t_list **env_lst)
{
	t_env	*var;
	t_list	*aux;

	var = new_env_var(token->string);
	if (!var)
		return (12);
	if (add_var_to_env(var, env_lst, token->string))
	{
		aux = ft_lstnew((void *)var);
		if (!aux)
			return (free_var_return_value(var, 12));
		ft_lstadd_back(env_lst, aux);
	}
	return (0);
}

int	builtin_export(t_list *tkn_lst, t_list **env_lst)
{
	t_list	*lst;
	t_token	*token;
	int		err;

	lst = *env_lst;
	tkn_lst = tkn_lst->next;
	token = tkn_lst->content;
	err = 0;
	if (!token || (token->type >= 0 || !token->string))
		return (print_export(lst));
	while (lst->next)
	{
		if (!is_valid_input(token->string, 0))
			err = 1;
		else if (export_loop(token, env_lst))
			return (12);
		tkn_lst = tkn_lst->next;
		token = tkn_lst->content;
		if (token && (token->type >= 0 || !token->string))
			break ;
	}
	set_or_return_exit_status(MODE_SET, err);
	return (err);
}
