# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kslik <kslik@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 10:13:56 by kslik             #+#    #+#              #
#    Updated: 2025/06/19 10:24:18 by kslik            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = ft_ls

# Compiler and flags
CC = gcc
CFLAGS = 
INCLUDES = -I.

# Source files
SRCS = main.c \
       ft_ls.c \
       file_list.c \
       display.c \
       utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Default target
all: $(NAME)

# Build the executable
$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

# Compile source files
%.o: %.c ft_ls.h
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)

# Rebuild everything
re: fclean all







help:
	@echo "Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  clean    - Remove object files"
	@echo "  fclean   - Remove object files and executable"
	@echo "  re       - Rebuild everything"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  uninstall- Remove from /usr/local/bin"
	@echo "  test     - Run basic tests"
	@echo "  debug    - Build with debug flags"
	@echo "  leaks    - Check for memory leaks with valgrind"
	@echo "  help     - Show this help message"




