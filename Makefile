##############################
### ARGUMENTS
NAME = cub3d
CC = gcc
LIB = MLX_LINUX/libmlx_Linux.a
C_FLAGS = -Wall -Wextra -Werror -I/usr/include -Iminilibx-linux -O3
MLX_LIB = -LMLX_LINUX -lmlx_Linux
X11_LIB = -L/usr/lib -lXext -lX11
MATH_LIB = -lm
ZLIB = -lz

##############################
### SOURCES
SRCS = src/main.c
OBJS = $(SRCS:.c=.o)


##############################
### RULES

all: $(LIB) $(NAME)

$(LIB):
	make -C ./MLX_LINUX

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_LIB) $(X11_LIB) $(MATH_LIB) $(ZLIB) -o $(NAME)
	
%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	make clean -C ./MLX_LINUX
	rm -f $(OBJS)
	

fclean: clean
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re