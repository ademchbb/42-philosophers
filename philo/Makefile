# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 12:26:18 by adchebbi          #+#    #+#              #
#    Updated: 2026/06/26 20:34:47 by adchebbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************** PROGRAM **************** #
#											#
NAME        = philo							#
#											#
# ***************************************** #


# **************** COMPILER *************** #
#											#
CC          = cc							#
CFLAGS      = -Wall -Wextra -Werror -pthread#
RM          = rm -f							#
#											#
# ***************************************** #


# **************** FILES ****************** #
#											#
SRCS        = main.c     \
              parse.c    \
              init.c     \
              routine.c  \
              forks.c    \
              monitor.c  \
              log.c      \
              time.c     \
              state.c    \
              cleanup.c
#											#
OBJS        = $(SRCS:.c=.o)					#
#											#
# ***************************************** #


# **************** COLORS ***************** #
#											#
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
BLUE        = \033[0;34m
RESET       = \033[0m
#											#
# ***************************************** #


# **************** RULES ****************** #
#											#
all: $(NAME)
#											#
$(NAME): $(OBJS)
	@printf "$(BLUE)🔧 Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN)✅ $(NAME) compiled successfully$(RESET)\n"
#											#
%.o: %.c
	@printf "$(YELLOW)🔨 Compiling $<$(RESET)\n"
	@$(CC) $(CFLAGS) -I includes -c $< -o $@
#											#
clean:
	@printf "$(RED)🧹 Cleaning object files$(RESET)\n"
	@$(RM) $(OBJS)
#											#
fclean: clean
	@printf "$(RED)🧼 Full clean$(RESET)\n"
	@$(RM) $(NAME)
	@sleep 1
	@clear
#											#
re: fclean all
#											#
.PHONY: all clean fclean re
#											#
# ***************************************** #
