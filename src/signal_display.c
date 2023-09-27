/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:30:23 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/24 17:32:36 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termios.h"

void	signal_display(int mode)
{
	struct termios	tc;

	tcgetattr(0, &tc);
	tc.c_lflag &= ~ECHOCTL;
	if (mode)
		tc.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
}
