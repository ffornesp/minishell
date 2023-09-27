/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:25:53 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/24 18:38:15 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_defs.h"
#include <stdlib.h>

void	init_data(t_data *var)
{
	var->hdoc_fds = NULL;
	var->read_pipe_fds = -1;
	var->next_read_fd = -1;
	var->write_pipe_fds[0] = -1;
	var->write_pipe_fds[1] = -1;
	var->hd_count = 0;
	var->hd_total = 0;
	var->process_id = 0;
	var->pipe_count = 0;
}
