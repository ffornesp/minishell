/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:52:31 by laugarci          #+#    #+#             */
/*   Updated: 2023/08/14 18:03:13 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libft.h"
#include "parser.h"
#include "libft_bonus.h"
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1

int	is_type(t_list *lst, int type)
{
	t_token	*aux;
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		aux = tmp->content;
		if (aux->type == type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	count_chars(t_list *lst)
{
	int		c;
	t_list	*tmp;
	t_token	*aux;

	c = 0;
	tmp = lst;
	while (tmp)
	{
		aux = tmp->content;
		if (aux->type == PIPE)
			c++;
		tmp = tmp->next;
	}
	return (c);
}

char	*ft_strtok(char *str, const char *del)
{
	static char	*token;
	char		*start;
	int			i;
	int			j;

	i = 0;
	if (str != NULL)
		token = str;
	if (token == NULL || *token == '\0')
		return (NULL);
	while (token[i] != '\0')
	{
		j = 0;
		while (del[j] != '\0')
		{
			if (token[i] == del[j])
			{
				i++;
				break ;
			}
			j++;
		}
		if (del[j] == '\0')
			break ;
	}
	if (token[i] == '\0')
		return (NULL);
	start = &token[i];
	while (token[i] != '\0')
	{
		j = 0;
		while (del[j] != '\0')
		{
			if (token[i] == del[j])
			{
				token[i] = '\0';
				i++;
				token += i;
				return (start);
			}
			j++;
		}
		i++;
	}
	token += i;
	return (start);
}

char	*find_command(t_list *lst)
{
	size_t	total_length;
	t_token	*token;
	t_list	*current;
	int		i;
	char	*result;
	size_t	offset;

	i = 0;
	total_length = 0;
	current = lst;
	while (current->next)
	{
		token = current->content;
		total_length += ft_strlen(token->string);
		current = current->next;
		i++;
	}
	result = malloc(sizeof(char) * (total_length + i));
	current = lst;
	offset = 0;
	while (current->next)
	{
		token = current->content;
		if (offset > 0)
		{
			result[offset] = ' ';
			offset++;
		}
		ft_strlcpy(result + offset, token->string, total_length + i);
		offset += ft_strlen(token->string);
		current = current->next;
	}
	result[total_length + i] = '\0';
	return (result);
}

char	*find_output(t_list *lst)
{
	t_list *tmp;
	t_token *token;
	char *output;

	tmp = lst;
	token = tmp->content;
	while(tmp->next)
	{
		if (token->type == 3)
		{
			output = malloc(sizeof(char) * ft_strlen(token->string) + 1);
			ft_strlcpy(output, token->string, ft_strlen(token->string) + 1);
		}
		tmp = tmp->next;
		token = tmp->content;
	}
	return (output);
}

void	exec_pipes(t_list *lst, char **env, int num_pipes)
{
	int		status;
	int		i;
	pid_t	pid;
	char	*command;
	int		**fds;
	t_list	*aux;
	char	*input;

	i = 0;
	fds = malloc(sizeof(int *) * num_pipes);
	while (i < num_pipes)
	{
		fds[i] = malloc(sizeof(int) * 2);
		pipe(fds[i]);
		i++;
	}
	i = 0;
	input = find_command(lst);
	command = ft_strtok(input, "|");
	while (command != NULL)
	{
		if (is_type(lst, 3) == 1)
		{
			char *output = find_output(lst);
		}
		pid = fork();
		if (pid == -1)
			exit(-1);
		else if (pid == 0)
		{
			if (i != 0)
			{
				close(fds[i - 1][WRITE_END]);
				dup2(fds[i - 1][READ_END], STDIN_FILENO);
				close(fds[i - 1][READ_END]);
			}
			if (i != num_pipes)
			{
				close(fds[i][READ_END]);
				dup2(fds[i][WRITE_END], STDOUT_FILENO);
				close(fds[i][WRITE_END]);
			}
			aux = save_tokens(command);
			exec_commands(aux, env);
			exit(1);
		}
		else
		{
			if (i != 0)
				close(fds[i - 1][READ_END]);
			if (i != num_pipes)
				close(fds[i][WRITE_END]);
		}
		command = ft_strtok(NULL, "|");
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
		close(fds[i][READ_END]);
		close(fds[i][WRITE_END]);
		i++;
	}
	i = 0;
	while (i <= num_pipes)
	{
		wait(&status);
		i++;
	}
}
