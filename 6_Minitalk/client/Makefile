NAME = client

CC = cc

# Add -Wall -Wextra -Werror when done
CFLAGS = -Wall -Wextra -Werror -g -I ../../98_include

LFLAGS = -L ../../99_lib -lftprintf -lft

SRCS = 	minitalk_client_main.c \
		minitalk_binary_conversions_c.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
