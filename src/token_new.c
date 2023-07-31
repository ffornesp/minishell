/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:17:14 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/31 18:30:03 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

t_token	*new_token(char	*string, int type, int quotes)
{
	t_token	*token;

	token = malloc(sizeof(t_token) * 2);
	if (!token)
		return (NULL);
	token->string = string;
	token->type = type;
	token->quotes = quotes;
	return (token);
}
