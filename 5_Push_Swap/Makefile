# All notes are now in the Makefile template
NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror -I ../98_include
LFLAGS = -L ../99_lib -lftprintf -lft

SRCS = 	push_swap_main.c \
		push_swap_input_management.c \
		push_swap_operations.c \
		push_swap_others.c \
		push_swap_algorithms.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all

.PHONY: all clean fclean re
