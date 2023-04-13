NAME		= philo

SRCS		= 	main.c\
				parsing.c\
				utils/ft_itoa.c\
				utils/ft_atoi.c\
				utils/ft_split.c\
				utils/ft_strjoin_ft_strlen.c
			
OBJS		= $(SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 