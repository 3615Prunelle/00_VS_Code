# All notes are now in the Makefile template
NAME = so_long

CC = cc

# Add -Wall -Wextra -Werror & run tests when almost done
CFLAGS = -I ../98_include
LFLAGS = -L ../99_lib -lmlx42 -lftprintf -lgetnextline -lglfw -lft #-lglfw goes with mlx42

SRCS = 	so_long_main_build.c \
		so_long_graphics.c \
		so_long_checkers.c \
		so_long_misc.c \
		so_long_free_functions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -g -o $@ $(OBJS) $(CFLAGS) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all

.PHONY: all clean fclean re
