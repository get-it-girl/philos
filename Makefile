NAME	= philo_one

HEADER	= ./philo.h

SRC		=	main.c init.c living.c tasks.c utils.c

OBJ		= ${patsubst %.c,%.o,${SRC}}

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

all:		${NAME}

${NAME}:	${OBJ} ${HEADER}
			${CC} ${OBJ} -o ${NAME} 

%.o : %.c
			${CC} ${CFLAGS} -c $< -o $@

clean:	
			${RM} ${OBJ}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
