NAME = test_parser
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Ilibft -Iincludes

SRC = main.c parsing.c neso.c updown.c utils.c getline.c get_next_line.c get_next_line_utils.c # ajoute tous tes fichiers parsing ici
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
