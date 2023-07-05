/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:32:21 by ffornes-          #+#    #+#             */
/*   Updated: 2023/07/05 12:42:22 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

void	parse_input(char *str, char *envp[]);

char	*get_path(char **cmd, char **envp);

char	*here_doc(char **input, char *envp[]);

void	put_error(char *str, int error_id);

int		exec_commands(char *input, char **env);

#endif
