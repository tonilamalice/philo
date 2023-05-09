NAME		= philo

SRCS		= 	main.c\
				parsing.c\
				utils/ft_atoi.c\
				time.c\
				death.c\
				thread.c
			
OBJS		= $(SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror #-fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 