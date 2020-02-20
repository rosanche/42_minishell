NAME = minishell

LIB = libft/libft.a

PRINTF = ft_printf/libftprintf.a

INC = minishell.h

FLAGS = -Wall -Wextra -Werror

SRCS = arraylist_add.c \
		arraylist_create.c \
		arraylist_destroy.c \
		arraylist_get.c \
		arraylist_grow.c \
		arraylist_index_of.c \
		arraylist_init.c \
		arraylist_remove.c \
		arraylist_remove_at.c \
		buildin_matcher.c \
		builtin.c \
		builtin_error.c \
		builtin_handler_cd.c \
		builtin_handler_echo.c \
		builtin_handler_env.c \
		builtin_handler_exit.c \
		builtin_handler_export.c \
		builtin_handler_pwd.c \
		builtin_handler_unset.c \
		destructor.c \
		env_compare.c \
		env_dump.c \
		env_finalize.c \
		env_get.c \
		env_initializer.c \
		env_loader.c \
		env_set.c \
		env_unset.c \
		env_var_creator.c \
		env_var_free.c \
		main.c \
		minishell.c \
		minishell_error.c \
		minishell_evaluator.c \
		minishell_exit.c \
		minishell_initialize.c \
		minishell_pre_loop.c \
		exec.c \
		evaluator_quote.c \
		evaluator_escape_backslash.c \

OBJ = $(SRCS:%.c=%.o)

%.o: %.c
	gcc -I $(INC) -c $< -o $@

all: $(NAME)

makelib:
	@$(MAKE) -C libft
	@$(MAKE) -C ft_printf

$(NAME) : $(OBJ) | makelib
	gcc -I $(INC) $(OBJ) $(LIB) $(PRINTF) -o $(NAME) 
	chmod +x minishell

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all