NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
src =	main.c\
		pipex_utils.c
		
OBJS = ${src:.c=.o}
REMOVE = rm -f
LIBFT = libftps.a
LDIR = libftps/

${NAME}:${OBJS} ${LDIR}${LIBFT}
		$(CC) $(CFLAGS) $(src) ${LDIR}${LIBFT} -o $(NAME)

all:${LDIR}${LIBFT} ${NAME}

${LDIR}${LIBFT}:
	${MAKE} -C ${LDIR}
	
clean :
		${REMOVE} ${OBJS}
		${REMOVE} ${LDIR}*.o

fclean :clean
		${REMOVE} ${NAME}
		${REMOVE} ${LDIR}${LIBFT}
re:fclean all
 
.PHONY: all clean fclean re

#LEAK_CHECK  := --leak-check=full
#LEAK_KIND   := --show-leak-kinds=all
#CHILDREN    := --trace-children=yes
#FD_TRACK    := --track-fds=yes