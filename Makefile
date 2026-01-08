CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -O3 -g -Ilibft
LDFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRCS = main.c parsing.c raycasting.c free_all.c keypress.c init.c raycasting_draw.c textures_init.c move.c rotate.c wall_texture.c utils_string.c render.c texture_buffer.c

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
	@make -C minilibx-linux clean
	@echo "Cleaned object files."

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned executable."

re: fclean all

# Phony targets
.PHONY: all clean fclean re