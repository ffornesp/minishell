/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:36:50 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/15 12:24:56 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

void	free_token(void *var)
{
	t_token	*token;

	token = (t_token *)var;
	if (token)
	{
		if (token->string)
			free(token->string);
		free(token);
	}
}
