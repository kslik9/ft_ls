NAME = ft_ls
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = main.c \
       ft_ls.c \
	   ft_ls2.c \
       file_list.c \
       display.c \
       utils.c \
	   simple.c \
	   time.c \
	   utils_2.c \
	   file_sort.c \
	   file_emrge.c \
	   utils_3.c
	   

OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

%.o: %.c ft_ls.h
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all