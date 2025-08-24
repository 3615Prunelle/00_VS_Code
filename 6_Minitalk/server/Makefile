NAME = server

CC = cc

# Add -Wall -Wextra -Werror when done
CFLAGS = -g -I ../../98_include

LFLAGS = -L ../../99_lib -lftprintf -lft

SRCS = 	minitalk_server_main.c \
		minitalk_binary_conversions_s.c

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
