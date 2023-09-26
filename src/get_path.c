/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:31:29 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/26 12:21:25 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

// Debugging - Must delete later
#include <stdio.h>

static void	put_error(char *str, int error_id)
{
	char	*aux;

	aux = NULL;
	if (error_id == 44)
		aux = ft_strjoin(str, ": error near unexpected token `\'\'\n");
	else if (error_id == 45)
		aux = ft_strjoin(str, ": error near unexpected token `\"\'\n");
	else if (error_id == 46)
		aux = ft_strjoin(str, ": error near unexpected token `|'\n");
	else if (error_id == 47)
		aux = ft_strjoin(str, ": error near unexpected token `<'\n");
	else if (error_id == 127)
		aux = ft_strjoin(str, ": No such file or directory\n");
	else if (error_id == 128)
		aux = ft_strjoin(str, ": unable to execute command XD\n");
	ft_putstr_fd(aux, 2);
	free(aux);
}

static char	**join_path_cmd(char **path, char *cmd)
{
	int		i;
	char	*aux;

	i = 0;
	while (path[i])
	{
		aux = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(aux);
		if (!path[i])
			return (NULL);
		aux = path[i];
		path[i] = ft_strjoin(path[i], cmd);
		free(aux);
		if (!path[i])
			return (NULL);
		i++;
	}
	return (path);
}

static char	*get_right_path(char **path, char *cmd)
{
	int		i;
	char	*out;

	i = 0;
	out = NULL;
	while (path[i])
	{
		if (!access(path[i], F_OK))
		{
			out = ft_strdup(path[i]);
			if (access(path[i], X_OK))
			{
				put_error(cmd, 128); // Error: Path has been found but it's not executable
				free(out);
				return (NULL);
			}
		}
		i++;
	}
	return (out);
}

static char	*get_path_util(char *str, char *cmd)
{
	char	**path;
	char	*out;

	str = ft_strtrim(str, "PATH=");
	path = ft_split(str, ':');
	free(str);
	if (!path)
		return (NULL);
	path = join_path_cmd(path, cmd);
	out = get_right_path(path, cmd);
	free_double((void **)path);
	return (out);
}


int	get_path(char *cmd, char **envp, char *dst)
{
	int		i;
	char	*aux;
	char	*out;

	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3 )
		|| cmd[0] == '/')
	{
		if (!access(cmd, F_OK))
		{
			if (access(cmd, X_OK))
				put_error(cmd, 128);
		}
		else
			put_error(cmd, 127);
		return (cmd);
	}
	i = 0;
	while (envp[i])
	{
		aux = ft_strnstr(envp[i++], "PATH", 4);
		if (aux != NULL)
			break ;
	}
	if (!aux)
	{
		put_error(cmd, 127); // Error: command not found
		return (NULL);
	}
	out = get_path_util(aux, cmd);
	if (!out)
		put_error(cmd, 127); // Error: command not found
	return (out);
}
