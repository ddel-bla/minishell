# --------------------------------
# -------- MAIN VARIABLE  --------
# --------------------------------

NAME	=	minishell

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

# ---------------------------------
# ---------- SRC & OBJS -----------
# ---------------------------------

SRC		=	./src/main.c \

OBJS	=	$(SRC:.c=.o)

# ---------------------------------
# --------- FLOWER POWER ----------
# ---------------------------------

PINK = \033[38;5;217m
TURQUOISE = \033[38;5;80m
YELLOW = \033[38;5;229m
RESET = \033[0m

START = "$(TURQUOISE)Compiling $(YELLOW) program...$(RESET)"
DONE = "$(TURQUOISE)Compilation $(YELLOW)complete!$(RESET)"
VALGRIND = "$(PINK)Running Valgrind...$(RESET)"
LEAKS = "$(TURQUOISE)[Leak Mode]$(RESET)"
DATA_RACES = "$(TURQUOISE)[Data Races Mode]$(RESET)"
CLEAN = "$(PINK)Cleaning $(YELLOW)files...$(RESET)"
CLEAN_DONE = "$(PINK)Clean $(TURQUOISE)complete!$(RESET)"

# ---------------------------------
# ------------ RULES --------------
# ---------------------------------
all		:	$(OBJS)
			@echo $(START)
			@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -lreadline
			@echo $(DONE)

clean	:
			@echo $(CLEAN)
			@$(RM) $(OBJS)
			@echo $(CLEAN_DONE)

fclean	:	clean
			@$(RM) $(NAME)
			@$(RM) philo

leaks	: 	$(OBJS_PHILO)
			@echo $(VALGRIND)
			@echo $(LEAKS)
			valgrind --leak-check=full ./$(NAME)

races	: 	$(OBJS_PHILO)
			@echo $(VALGRIND)
			@echo $(DATA_RACES)
			valgrind --tool=helgrind ./$(NAME)

.PHONY	:	all fclean re clean

re		:	fclean all
