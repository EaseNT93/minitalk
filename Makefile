NAME_C = client

NAME_S = server

SRC_C =	client.c

SRC_S =	server.c

OBJ_C = $(SRC_C:.c=.o)

OBJ_S = $(SRC_S:.c=.o)

NAME_C_BONUS = client_bonus

NAME_S_BONUS = server_bonus

SRC_C_BONUS =	client_bonus.c

SRC_S_BONUS =	server_bonus.c

OBJ_C_BONUS = $(SRC_C_BONUS:.c=.o)

OBJ_S_BONUS = $(SRC_S_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

RM = rm -rf

all: $(NAME_S) $(NAME_C)

$(NAME): $(NAME_S) $(NAME_C)

$(NAME_S): $(OBJ_S)
			$(CC) $(CFLAGS) $(OBJ_S) -o $(NAME_S)

$(NAME_C): $(OBJ_C)
			$(CC) $(CFLAGS) $(OBJ_C) -o $(NAME_C)

$(NAME_S_BONUS): $(OBJ_S_BONUS)
			$(CC) $(CFLAGS) $(OBJ_S_BONUS) -o $(NAME_S_BONUS)

$(NAME_C_BONUS): $(OBJ_C_BONUS)
			$(CC) $(CFLAGS) $(OBJ_C_BONUS) -o $(NAME_C_BONUS)

bonus: $(NAME_S_BONUS) $(NAME_C_BONUS)

clean:
		$(RM) $(OBJ_S) $(OBJ_C) $(OBJ_S_BONUS) $(OBJ_C_BONUS)

fclean: clean
		$(RM) $(NAME_S) $(NAME_C) $(NAME_S_BONUS) $(NAME_C_BONUS)

re: fclean all

.PHONY:	all fclean clean re bonus