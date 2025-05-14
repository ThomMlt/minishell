NAME = libgnl.a

FLAGS = -Wall -Werror -Wall -g

SRCS = get_next_line_utils.c \
		get_next_line.c

OBJS = $(SRCS:.c=.o)

CC = cc 

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c 
	$(CC) $(FLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all