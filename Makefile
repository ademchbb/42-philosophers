# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 12:26:18 by adchebbi          #+#    #+#              #
#    Updated: 2026/06/26 16:17:33 by adchebbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************** PROGRAM **************** #
NAME        = philo

# **************** COMPILER *************** #
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread
RM          = rm -f

# **************** PATHS ****************** #
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = includes

# Dossiers de sources (par theme)
SRC_SUBDIRS = $(SRC_DIR) \
              $(SRC_DIR)/parsing \
              $(SRC_DIR)/init \
              $(SRC_DIR)/simulation \
              $(SRC_DIR)/utils

# vpath : ou make doit chercher les .c (objets regroupes dans obj/)
vpath %.c $(SRC_SUBDIRS)

# **************** FILES ****************** #
SRCS        = main.c    \
              parse.c   \
              init.c    \
              cleanup.c \
              routine.c \
              forks.c   \
              monitor.c \
              log.c     \
              time.c    \
              state.c

OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# **************** COLORS ***************** #
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
BLUE        = \033[0;34m
RESET       = \033[0m

# **************** RULES ****************** #
all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(BLUE)🔧 Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN)✅ $(NAME) compiled successfully$(RESET)\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(YELLOW)🔨 Compiling $<$(RESET)\n"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@printf "$(RED)🧹 Cleaning object files$(RESET)\n"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@printf "$(RED)🧼 Full clean$(RESET)\n"
	@$(RM) $(NAME)
	@sleep 1
	@clear

re: fclean all

.PHONY: all clean fclean re
