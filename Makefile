.SILENT:

# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror

# Directories
SRC_DIR := ./src
OBJ_DIR := ./obj

# Files
SRCS    := $(SRC_DIR)/main.c $(SRC_DIR)/handler.c
OBJS    := $(OBJ_DIR)/main.o $(OBJ_DIR)/handler.o
NAME    := philo
HEADERS := philo.h

# Colors and emojis
GREEN   := \033[0;32m
YELLOW  := \033[38;5;226m
ORANGE  := \033[38;5;208m
RESET   := \033[0m
CHECK   := ✅

# Rules
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilation successful! $(CHECK)$(RESET)"

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/handler.o: $(SRC_DIR)/handler.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/handler.c -o $(OBJ_DIR)/handler.o

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(ORANGE)Object files cleaned! $(CHECK)$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(ORANGE)Executable $(NAME) removed! $(CHECK)$(RESET)"

re: fclean all

.PHONY: all clean fclean re
