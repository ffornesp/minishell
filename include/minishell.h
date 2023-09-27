/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:32:21 by ffornes-          #+#    #+#             */
/*   Updated: 2023/09/27 16:10:01 by laugarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft_defs.h"
# include "minishell_defs.h"

t_list		*set_env(char *envp[]);
void		init_data(t_data *var);

void		free_var(t_env *var);
int			free_var_return_value(t_env *var, int value);
t_env		*new_env_var(char *str);
t_env		*char_to_tenv(char *input);
char		**envlst_to_charpp(t_list *lst);

int			**pipe_fds(int num_pipes);

int			get_path(char *cmd, char **envp, char **dst);

int			exec_commands(t_list *lst, char **env);
int			start_execution(t_list *lst, t_list **env_lst, char **env);
int			gen_child(t_list *lst, t_list **env_lst, t_data *data, char **env);
int			get_child_status(int pid);
int			builtin_check(t_list *lst, t_list **env_lst, char **env);

int			type_count(t_list *lst, int type);
int			p_type_count(t_list *lst, int type);

int			exec_pipes(char **env, int num_pipes, t_list *lst);

int			count_args(t_list *lst);

int			**close_pipes(int **fds, int num_pipes);

char		*find_command(t_list *lst);
int			find_input(t_list *lst, char **dst, int type1, int type2);
char		*find_output(t_list *lst);

int			exec_redirect(t_list *lst);

int			count_list(t_list *lst);
int			total_input_len(t_list *lst);
int			here_doc(t_list *lst, int id);
void		create_files(t_list *lst);

t_list		*process_list(t_list *lst, int i);
int			check_redirect(t_list *lst, int type1, int type2);
t_list		*move_to_pipe(t_list *lst);
int			check_infile(t_list *lst);

int			process_is_type(t_list *lst, int type);
int			execution(t_list *lst, t_list **env_lst, t_data *data, char **env);
int			dup_read(t_list *lst, t_data *data);
int			dup_write(t_list *lst);

	//	BUILTINS
int			exec_env(char **env);

int			exec_pwd(void);

int			exec_echo(t_list *lst);

int			builtin_export(t_list *tkn_lst, t_list **env_lst);
t_env		*export_set_value(t_env *env_var, t_env *var, char *str);
int			free_key_and_return(t_env *var);

int			builtin_unset(t_list *lst, t_list **env_lst);

int			builtin_cd(t_list *lst, t_list **env_lst);

void		builtin_exit(char *input);
int			check_digits(char *input);
void		put_numeric_error(char *input);
void		exit_check(t_list *lst, int *err, t_token *token);
	//	ERRORS
int			error_exec(char *cmd, char *error_message, int value);
int			print_error_and_return(char *error_message, int value);
int			invalid_identifier(char *builtin, char *str);

int			set_or_return_exit_status(int mode, int value);
int			set_or_return_state(int mode, int value);
	//	SIGNALS
int			*signal_handler(void);
void		signal_display(int mode);
void		signal_setup(int flag);

int			free_double_and_return(void **src, int error);
#endif
