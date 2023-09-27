/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:48:17 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/25 19:40:12 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "parser.h"

static int	is_valid_input(char *str, int i)
{
	int	flag;

	flag = 0;
	if (!str[i])
		return (invalid_identifier("unset", ""));
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
			return (invalid_identifier("unset", str));
		i++;
	}
	return (1);
}

static void	builtin_unset_util(t_list **previous, t_list *var_lst, \
			t_list **env_lst)
{
	t_list	*aux;

	aux = *previous;
	if (aux)
	{
		aux->next = var_lst->next;
		var_lst->next = NULL;
	}
	else
		*env_lst = var_lst->next;
	ft_lstclear(&var_lst, (void *)free_var);
}

static int	unset_loop(t_token *token, t_list **env_lst)
{
	t_list	*previous;
	t_list	*var_lst;
	t_env	*var;

	var_lst = *env_lst;
	previous = NULL;
	while (var_lst)
	{
		var = var_lst->content;
		if (!ft_strncmp(var->key, token->string, ft_strlen(token->string) + 1))
		{
			builtin_unset_util(&previous, var_lst, env_lst);
			break ;
		}
		previous = var_lst;
		var_lst = var_lst->next;
	}
	return (0);
}

int	builtin_unset(t_list *lst, t_list **env_lst)
{
	t_token	*token;
	t_list	*var_lst;
	int		err;

	lst = lst->next;
	token = lst->content;
	if ((!token->string || !*token->string) && token->quotes < 0)
		return (0);
	err = 0;
	var_lst = *env_lst;
	while (lst->next)
	{
		if (!is_valid_input(token->string, 0))
			err = 1;
		unset_loop(token, env_lst);
		lst = lst->next;
		token = lst->content;
		if ((!token->string || !*token->string) && token->quotes < 0)
			break ;
		else if (token && token->type >= 0)
			break ;
	}
	return (err);
}
