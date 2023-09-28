# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 15:00:09 by ffornes-          #+#    #+#              #
#    Updated: 2023/09/28 11:26:14 by ffornes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/
SRC_FILES = minishell.c \
			init_env.c init_data.c \
			env_var_free.c env_var_new.c env_var_to_charpp.c \
			parse_input.c clean_input.c clean_input_utils.c split_input.c \
			expansion.c expansion_utils.c expansion_update.c \
			get_path.c exec_commands.c exec_here_doc.c \
			start_execution.c \
			exec_redirec.c utils.c find_command.c \
			quotes.c \
			token_new.c token_free.c token_save.c token_type.c \
			token_process.c token_process_rm.c \
			subtoken_process.c subtoken_count.c subtoken_join.c token_organize.c \
			builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_exit.c builtin_exit_utils.c \
			builtin_export.c builtin_export_utils.c \
			builtin_pwd.c \
			builtin_unset.c \
			errors.c syntax_error.c \
			process_list.c \
			signals.c signal_display.c \
			utils_free.c \
			exit_status.c execution.c execution_utils.c dup_read_write.c token_clean_rd.c

OBJ_DIR = objs/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP_FILES = $(SRC_FILES:.c=.d)
DEPS = $(addprefix $(OBJ_DIR), $(DEP_FILES))

LIBFT = libft/libft.a

CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror -MMD #-fsanitize=address
RM = 		rm -f
INCLUDE =	-I include/ -I libft/include/ -I ~/.brew/Cellar/readline/8.2.1/include/

all:		m_libft $(NAME)
#			@say -v Kyoko "頑張ってください"

m_libft:
			@make -C libft/

$(NAME):	$(OBJ_DIR) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -L libft/ -lft -o $@ -L ~/.brew/Cellar/readline/8.2.1/lib/ -lreadline -lhistory -ltermcap


$(OBJ_DIR):
			@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBFT) Makefile
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			$(RM) $(OBJS) $(DEPS)
			@make -C libft/ clean

fclean:	clean
		$(RM) -r $(OBJ_DIR)
		$(RM) $(NAME)
		@make -C libft/ fclean

re:	fclean all

-include $(DEPS)

.PHONY: all clean fclean re
