GREEN=\033[0;32m
STOP=\033[0m

define PRINT_LOADING_BAR
	@progress=$$(echo "scale=2; $(1) / $(2) * 100" | bc); \
	percentage=$$(printf "%.0f" $$progress); \
	echo "Progress: [$$percentage%]"
endef

NAME    = minishell
SRC     = src/lexer/ft_str_utils.c\
			src/lexer/ft_str_utils_s.c\
			src/lexer/ft_lexer.c\
			src/lexer/ft_lexer_utils.c\
			src/lexer/ft_token_cases.c\
			src/parser/ft_parser.c\
			src/parser/ft_parser_utils.c\
			src/parser/ft_parser_utils_2.c\
			src/parser/ft_cmd_utils.c\
			src/ft_signals.c\
			utils/get_next_line/ft_get_next_line.c\
			utils/get_next_line/ft_get_next_line_utils.c\
			src/exec/ft_exec_append.c\
			src/exec/ft_exec_exec.c\
			src/exec/ft_exec_heredoc.c\
			src/exec/ft_exec_input_red.c\
			src/exec/ft_exec_pipex_bonus.c\
			src/exec/ft_exec_pipex_utls_bonus.c\
			src/exec/ft_exec_redirect.c\
			src/exec/ft_exec_parsing.c\
			src/exec/ft_error.c\
			src/exec/ft_free.c\
			src/exec/ft_lexer.c\
			src/exec/ft_meta_mgmt.c\
			src/expander/ft_expander.c\
			src/expander/ft_expander_utils.c\
			src/built_ins/ft_cd.c\
			src/built_ins/ft_echo.c\
			src/built_ins/ft_env.c\
			src/built_ins/ft_exit.c\
			src/built_ins/ft_export.c\
			src/built_ins/ft_pwd.c\
			src/built_ins/ft_unset.c\
			src/built_ins/ft_built_in.c\
			main.c
OBJ     = $(SRC:.c=.o)
CC      = gcc
CFLAGS  = -g -Wall -Werror -Wextra
COMP    = $(CC) $(CFLAGS)
RM      = rm -f
DIR_INC	= -Iutils/
LIB_LIB	= utils/libft.a
RDL_PAT = $(shell brew --prefix readline)
RDL_LIB = -lreadline -lhistory -L $(RDL_PAT)/lib
RDL_INC = -I $(RDL_PAT)/include
TOT_FIL	= $(words $(SRC))

all:    $(NAME)

$(NAME): $(OBJ) $(LIB_LIB)
		@$(COMP) -fsanitize=address -g3 $(OBJ) -o $(NAME) $(LIB_LIB) $(RDL_LIB)
		@echo "$(GREEN)Compilation completed.$(STOP)"

%.o: %.c
		@$(CC) $(CFLAGS) $(DIR_INC) $(RDL_INC) -c $< -o $@
		@$(eval FILES_DONE := $(shell echo $$(($(FILES_DONE) + 1))))
		@$(call PRINT_LOADING_BAR,$(FILES_DONE),$(TOT_FIL))

$(LIB_LIB):
		@$(MAKE) -C utils

clean:
		@$(RM) $(OBJ)
		@$(MAKE) -C utils clean
		@echo "$(GREEN)Cleaning completed.$(STOP)"

fclean: clean
		@$(RM) $(NAME)
		@$(MAKE) -C utils fclean

re:     fclean all
