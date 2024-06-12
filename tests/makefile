TARGET = tester
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directorios
SRC_DIR = ../src/lexer
TEST_DIR = lexer
OBJ_DIR = obj

# Archivos fuente
SRC_FILES = $(SRC_DIR)/ft_quotes.c
TEST_FILES = $(TEST_DIR)/main.c $(TEST_DIR)/test_ft_quotes.c

# Archivos objeto
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES))) $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(TEST_FILES)))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
