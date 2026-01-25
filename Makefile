CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -O3 -g -Ilibft
LDFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRCS = main.c \
	player/init.c player/move.c player/rotate.c \
	parsing/load_map.c player/handle_move.c \
	mlx/init.c mlx/render.c \
	raycasting/cast_ray.c raycasting/dda_init.c raycasting/dda_loop.c \
	raycasting/ray_dir.c raycasting/texture.c

OBJS = $(SRCS:.c=.o)

NAME = cub3d
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS += -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@make -C minilibx-linux
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "cub3d compiled!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Cleaned object files."

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned executable."

re: fclean all

.PHONY: all clean fclean re