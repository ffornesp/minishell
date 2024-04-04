/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:31:29 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 17:59:02 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

#include <stdio.h>

static char	**join_path_cmd(char **path, char *cmd, int i)
{
	char	*aux;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		aux = ft_strjoin(path[i], "/");
		if (!aux)
			return (free_double((void **)path));
		tmp = path[i];
		path[i] = aux;
		free(tmp);
		aux = ft_strjoin(path[i], cmd);
		if (!aux)
			return (free_double((void **)path));
		tmp = path[i];
		path[i] = aux;
		free(tmp);
		i++;
	}
	return (path);
}

static int	get_right_path(char *cmd, char **path, char **dst)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (!access(path[i], F_OK))
		{
			if (access(path[i], X_OK))
				return (print_error_and_return("Permission denied\n", 128));
			else
			{
				*dst = ft_strdup(path[i]);
				if (!dst)
					return (12);
				return (0);
			}
		}
		i++;
	}
	return (error_exec(cmd, "command not found\n", 127));
}

static int	get_path_util(char *str, char *cmd, char **dst)
{
	char	**path;
	char	*tmp;
	int		err;

	while (*str && *str != '=')
		str++;
	str++;
	tmp = ft_strdup(str);
	if (!tmp)
		return (12);
	path = ft_split(tmp, ':');
	free(tmp);
	if (!path)
		return (12);
	path = join_path_cmd(path, cmd, -1);
	if (!path)
		return (12);
	err = get_right_path(cmd, path, dst);
	free_double((void **)path);
	if (err)
		return (err);
	return (0);
}

static int	is_absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK))
		{
			if (access(cmd, X_OK))
				return (error_exec(cmd, "Permission denied\n", 128));
		}
		else
			return (error_exec(cmd, "No such file or directory\n", 127));
		return (1);
	}
	return (0);
}

int	get_path(char *cmd, char **envp, char **dst)
{
	int		i;
	int		err;
	char	*aux;

	err = is_absolute_path(cmd);
	if (err == 1)
	{
		*dst = ft_strdup(cmd);
		return (0);
	}
	else if (err)
		return (err);
	i = 0;
	aux = NULL;
	while (envp[i] && !aux)
		aux = ft_strnstr(envp[i++], "PATH", 4);
	if (!aux)
		return (error_exec(cmd, "command not found\n", 127));
	err = get_path_util(aux, cmd, dst);
	if (err == 12)
		return (print_error_and_return("Cannot allocate memory\n", 12));
	return (err);
}
