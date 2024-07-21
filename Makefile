# --------------------------------
# -------- MAIN VARIABLES --------
# --------------------------------

NAME	=	minishell

CC		=	gcc

CFLAGS	=	-g -Wall -Wextra -Werror #-fsanitize=address

RM		=	rm -f

# ---------------------------------
# ---------- SRC & OBJS -----------
# ---------------------------------

SRC		=	./src/main.c \
		./src/lexer/lexer.c \
		./src/lexer/token_types.c \
		./src/lexer/validation.c \
		./src/lexer/utils/token_struct.c \
		./src/lexer/utils/token_struct2.c \
		./src/parser/parser.c \
		./src/parser/utils/command_struct.c \
		./src/parser/utils/command_struct2.c \
		./src/parser/utils/redir_struct.c \
		./src/parser/utils/redir_struct2.c \
		./src/parser/utils/utils.c \
		./src/env/env.c \
		./src/env/utils/env_struct.c \
		./src/env/utils/env_struct2.c \
		./src/env/utils/env_struct3.c \
		./src/builtins/builtins.c \
		./src/builtins/utils.c \
		./src/builtins/env/ft_env.c \
		./src/builtins/unset/ft_unset.c \
		./src/builtins/export/ft_export.c \
		./src/builtins/pwd/ft_pwd.c \
		./src/builtins/echo/ft_echo.c \
		./src/builtins/exit/ft_exit.c \
		./src/builtins/cd/ft_cd.c \
		./src/utils/design.c \
		./src/utils/main_utils.c \
		./src/utils/utils.c \
		./src/utils/utils2.c \
		./src/utils/utils3.c \
		./src/expander/expander.c \
		./src/expander/expand_cases.c \
		./src/expander/utils/utils.c \
		./src/expander/utils/utils2.c \
		./src/expander/utils/utils3.c \
		./src/utils/func_utils.c \
		./src/executer/executer.c \
		./src/executer/utils/exec_exe.c \
		./src/executer/utils/exec_here.c \
		./src/executer/utils/exec_pid.c \
		./src/executer/utils/exec_path.c \
		./src/executer/utils/exec_pipe.c \
		./src/executer/utils/exec_redir.c \
		./src/signals/signals.c
		

OBJS	=	$(patsubst ./src/%.c, ./build/%.o, $(SRC))

# ---------------------------------
# ---------- LIBRARIES -----------
# ---------------------------------
#
# ............ LIBFT ..............

LIBFT	=	./lib/libft
LIBFT_A	=	$(LIBFT)/libft.a

# ---------------------------------
# --------- FLOWER POWER ----------
# ---------------------------------

PINK		=	\033[38;5;217m
TURQUOISE	=	\033[38;5;80m
YELLOW		=	\033[38;5;229m
RESET		=	\033[0m

START		=	"$(TURQUOISE)Compiling $(YELLOW) program...$(RESET)"
DONE		=	"$(TURQUOISE)Compilation $(YELLOW)complete!$(RESET)"
VALGRIND	=	"$(PINK)Running Valgrind...$(RESET)"
LEAKS		=	"$(TURQUOISE)[Leak Mode]$(RESET)"
DATA_RACES	=	"$(TURQUOISE)[Data Races Mode]$(RESET)"
CLEAN		=	"$(PINK)Cleaning $(YELLOW)files...$(RESET)"
CLEAN_DONE	=	"$(PINK)Clean $(TURQUOISE)complete!$(RESET)"

# ---------------------------------
# ------------ RULES --------------
# ---------------------------------
all			: $(NAME)

$(NAME)		: $(OBJS)
	@echo $(START)
	@make -C $(LIBFT) -f Makefile
	@$(CC) $(CFLAGS) -o $@ $^ -lreadline $(LIBFT_A)
	@echo $(DONE)


./build/%.o	: ./src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean		:
	@echo $(CLEAN)
	@make -C $(LIBFT) clean
	@$(RM) -r ./build
	@echo $(CLEAN_DONE)

fclean		: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT) fclean
	@$(RM) philo

leaks		: re
	@echo $(VALGRIND)
	@echo $(LEAKS)
	valgrind --leak-check=full --track-origins=yes -s ./$(NAME)

races		: re
	@echo $(VALGRIND)
	@echo $(DATA_RACES)
	valgrind --tool=helgrind ./$(NAME)

re			:	fclean all

.PHONY		: all fclean re clean leaks races
