/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:34:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 19:01:38 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	exp_token_util(char *string, t_token **tkn, t_list **lst)
{
	t_list	*aux;
	t_token	*token;

	aux = *lst;
	token = *tkn;
	if (!ft_strchr(string, ' ') || token->quotes > 0)
	{
		token->string = string;
		aux->content = token;
		return (1);
	}
	return (0);
}

char	*string_exp_token(t_token *tkn, char **envp)
{
	char	*string;

	if (tkn->type == TOKEN_APPEND && !ft_strncmp(tkn->string, "$\0", 2))
		string = ft_strdup("");
	else
		string = expand_evals(tkn->string, envp);
	return (string);
}

static t_list	*exp_token(t_list *lst, t_token *tkn, char **envp)
{
	t_list	*new_list;
	t_list	*aux;
	char	*string;

	string = string_exp_token(tkn, envp);
	if (!string)
		return (NULL);
	if (exp_token_util(string, &tkn, &lst))
		return (lst);
	new_list = save_tokens(string);
	if (!new_list)
		return (NULL);
	free(lst->content);
	free(string);
	lst->content = new_list->content;
	aux = new_list;
	new_list = new_list->next;
	free(aux);
	aux = lst->next;
	lst->next = new_list;
	while (new_list->next)
		new_list = new_list->next;
	new_list->content = aux->content;
	new_list->next = aux->next;
	return (lst);
}

static int	process_tokens_util(t_list **token_list, char *envp[])
{
	t_list	*tmp_lst;
	t_token	*aux;

	tmp_lst = *token_list;
	aux = tmp_lst->content;
	while (aux->string)
	{
		if (remove_quotes(&aux))
			return (print_error_and_return("Cannot allocate memory\n", 12));
		if (aux->type != HERE_DOC && ft_strchr(aux->string, '$')
			&& (aux->quotes == 2 || !aux->quotes))
		{
			tmp_lst = exp_token(tmp_lst, aux, envp);
			if (!tmp_lst)
				return (print_error_and_return("Cannot allocate memory\n", 12));
		}
		tmp_lst = tmp_lst->next;
		aux = tmp_lst->content;
	}
	return (0);
}

int	process_tokens(t_list **token_list, char *envp[])
{
	int	err;

	set_type(token_list);
	if (syntax_error_check(*token_list))
		return (258);
	clean_redirects(token_list);
	if (process_subtokens(token_list))
		return (print_error_and_return("Cannot allocate memory\n", 12));
	err = process_tokens_util(token_list, envp);
	if (err)
		return (err);
	if (join_subtoken(token_list))
		return (print_error_and_return("Cannot allocate memory\n", 12));
	remove_duplicates(token_list);
	return (0);
}
