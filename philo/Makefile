# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 14:29:53 by jmatute-          #+#    #+#              #
#    Updated: 2022/08/08 18:53:40 by jmatute-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= philo.c utils.c cycle_routine.c create_and_init.c

LIBFT_DIR	= libft/

OBJS	= ${SRCS:.c=.o}

NAME	= philo

CC		= gcc 

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror  -pthread #-g3 #-fsanitize=thread 
	
${NAME}:	${OBJS} philo.h Makefile 
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}  

			@echo "COMPILATION IS FINISHED"

all:		${NAME}

clean:
			${RM} ${OBJS} libft.a

fclean:		clean
			${RM} ${NAME}

re:			fclean all