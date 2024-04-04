/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:21:07 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/25 12:29:04 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"
#include "minishell.h"
#include "minishell_defs.h"
#include <stdio.h>

static void	*free_var_and_list_and_return(t_env *var, t_list *lst)
{
	if (var)
		free_var(var);
	if (lst)
		ft_lstclear(&lst, (void *)free_var);
	return (NULL);
}

static int	check_for_oldpwd(t_list *lst)
{
	t_env	*var;

	while (lst)
	{
		var = lst->content;
		if (!ft_strncmp(var->key, "OLDPWD\0", 7))
			return (1);
		lst = lst->next;
	}
	return (0);
}

static t_list	*lst_oldpwd(void)
{
	t_env	*var;
	t_list	*out;

	var = new_env_var("OLDPWD");
	if (!var)
		return (NULL);
	out = ft_lstnew((void *)var);
	if (!out)
		return (free_var_and_list_and_return(var, NULL));
	return (out);
}

t_list	*set_env(char *envp[])
{
	t_list	*out;
	t_list	*aux;
	t_env	*var;

	out = NULL;
	while (*envp)
	{
		var = new_env_var(*envp);
		if (!var)
			return (free_var_and_list_and_return(var, NULL));
		aux = ft_lstnew((void *)var);
		if (!aux)
			return (free_var_and_list_and_return(var, out));
		ft_lstadd_back(&out, (void *)aux);
		envp++;
	}
	if (check_for_oldpwd(out))
		return (out);
	aux = lst_oldpwd();
	if (!aux)
		return (free_var_and_list_and_return(NULL, out));
	ft_lstadd_back(&out, aux);
	return (out);
}
