NAME        = philo
OBJDIR      = objects/
SRCDIR      = src/

CC          = gcc
CFLAGS      = -Werror -Wextra -Wall

YELLOW      = \033[1;33m
GREEN       = \033[1;32m
RED         = \033[1;31m
RESET       = \033[0m

SRC         = algo.c free.c handler.c init.c main.c monitoring.c output.c \
              sim.c time.c utils.c
SRCS        = $(addprefix $(SRCDIR), $(SRC))
OBJ         = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)./$(NAME) ready$(RESET)"

clean:
	@echo "$(RED)Removing object files...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re