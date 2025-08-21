# Makefile pour Eval (l'original a été backup)
NAME = so_long

CC = cc

# Vérfier si ok
CFLAGS = -Wall -Wextra -Werror -g -I ./get_next_line -I ./ft_printf -I ./MLX42/include -I ./libft
LFLAGS = -L ./get_next_line -L ./ft_printf -L ./MLX42/build -L ./libft -lmlx42 -lgetnextline -lftprintf -lglfw -lft #-lglfw goes with mlx42

SRCS = 	so_long_main_build.c \
		so_long_graphics.c \
		so_long_checkers.c \
		so_long_path_check.c \
		so_long_misc.c \
		so_long_handler_bonus.c \
		so_long_free_functions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# Vérfier si ok
$(NAME): $(OBJS) comp_mlx42 comp_libft comp_printf comp_gnl
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Vérfier si ok - Commande trouvée dans exemple Makefile sur page github de MLX42
comp_mlx42 :
	@cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4

comp_libft :
	$(MAKE) -C ./libft

comp_printf :
	$(MAKE) -C ./ft_printf

comp_gnl :
	$(MAKE) -C ./get_next_line

clean:
	rm -f $(OBJS)

# Vérfier si dernière commande ok
fclean: clean
	rm -f $(NAME)
	rm -f a.out
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./ft_printf fclean
	$(MAKE) -C ./get_next_line fclean
	rm -rf ./MLX42//build

re: fclean all

.PHONY: all clean fclean re
