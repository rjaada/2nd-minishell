NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/
LIBFT_DIR = libraries/libft/

# Source files
SRC_FILES = main.c \
			lexer/lexer_init.c \
			lexer/lexer_token.c \
			lexer/lexer_word.c \
			lexer/lexer_utils.c \
			lexer/lexer_expand.c \
			expander/expander.c \
			parser/parser.c \
			parser/parser_utils.c \
			signals/signals.c \
			utils/utils.c \
			utils/utils_mem.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Libraries
LIBFT = $(LIBFT_DIR)libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

# Includes
INC = -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re