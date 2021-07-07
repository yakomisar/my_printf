NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f

SRCS = ft_printf.c\
		ft_parse_flags.c\
		ft_go_print.c\
		my_gang.c\
		my_gang2.c\
		my_gang3.c\
		print_c_s.c\
		print_p.c\
		print_p_help.c\
		print_d.c\
		print_u.c\
		print_x.c

OBJS = $(SRCS:%.c=%.o)

LIBFT_PATH = ./libft/

%.o: %.c libftprintf.h
	$(CC) $(CFLAGS) -I . -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re
