#include <stdio.h> // delete later
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct s_list
{
	const char	*str;
	va_list		arguments;
	int			type;
	int			width;
	int			minus;
	int			zero;
	int			precision;
	int			star;
	int			length;
}				t_list;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_get_ptrlen(unsigned long long arg)
{
	int	i;

	i = 0;
	while (arg != 0)
	{
		arg = arg / 16;
		i++;
	}
	return (i);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	char		*s;
	int			result;
	int			i;
	short int	sign;

	i = 0;
	sign = 1;
	result = 0;
	s = (char *)str;
	while (s[i] == '\t' || s[i] == '\r' || s[i] == '\n'
		   || s[i] == ' ' || s[i] == '\f' || s[i] == '\v')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{	
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = (result * 10) + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

void	ft_clean_flags(t_list *clean)
{
	clean->type = 0;
	clean->width = 0;
	clean->minus = 0;
	clean->zero = 0;
	clean->star = 0;
	clean->precision = -1;
}

void	ft_parse_flags(t_list *flags)
{
	while (*flags->str == '0' || *flags->str == '-')
	{
		if (*flags->str == '-')
		{
			flags->minus = 1;
			flags->zero = 0;
			while (*flags->str == '0' || *flags->str == '-')
				flags->str++;
		}
		else if (*flags->str == '0')
			flags->zero = 1;
		flags->str++;
	}
}

void	ft_parse_width(t_list *width)
{
	int	len;

	len = 0;
	if (*width->str == '*')
	{
		width->width = va_arg(width->arguments, int);
		if (width->width < 0)
		{
			width->width = width->width * (-1);
			width->minus = 1;
		}
		width->str++;
	}
	if (*width->str >= '0' && *width->str <= '9')
	{
		while (*width->str >= '0' && *width->str <= '9')
		{
			len = len * 10 + (*width->str - '0');
			width->str++;
		}
	}
	width->width = len;
}

void	ft_parse_precision(t_list *list)
{
	int	pre;

	pre = 0;
	if (*list->str == '.')
	{
		list->str++;
		if (*list->str == '*')
		{
			list->precision = va_arg(list->arguments, int);
			if (list->precision < 0)
				list->precision = 0;
			list->precision++;
		}
		if (*list->str >= '0' && *list->str <= '9')
		{
			while (*list->str >= '0' && *list->str <= '9')
			{
				pre = pre * 10 + (*list->str - '0');
				list->str++;
			}
		}
	}
	list->precision = pre;
}

void	ft_detect_format(t_list *check)
{
	int	format;

	format = 0;
	if (*check->str == 'c')
		format = 1;
	if (*check->str == 's')
		format = 2;
	if (*check->str == 'p')
		format = 3;
	if (*check->str == 'd' || *check->str == 'i')
		format = 4;
	if (*check->str == 'u')
		format = 5;
	if (*check->str == 'x' || *check->str == 'X')
		format = 6;
	if (*check->str == '%')
		format = 7;
	check->type = format;
}

void	ft_print_symbol(char symbol, int width, t_list *check)
{
	while ((width - 1) > 0)
	{
		ft_putchar(symbol);
		width--;
		check->length++;
	}
	check->length++;
}

void	ft_char(t_list *check)
{
	char	c;

	c = va_arg(check->arguments, int);
	if (check->minus == 1)
	{
		ft_putchar(c);
		ft_print_symbol(' ', check->width, check);
	}
	else if (check->minus != 1)
	{
		ft_print_symbol(' ', check->width, check);
		ft_putchar(c);
	}
	check->str++;
}

void	ft_print_space(char c, t_list *check, int len)
{
	while (len > 0)
	{
		ft_putchar(c);
		len--;
		check->length++;
	}	
}

void	ft_putstr(char *s, int len, t_list *check)
{
	int	i;
	
	i = 0;
	while (len > 0)
	{
		ft_putchar(s[i]);
		check->length++;
		len--;
		i++;
	}
}

void	ft_string(t_list *check)
{
	char	*s;
	int		w;

	s = va_arg(check->arguments, char *);
	if (s == NULL)
		s = "(null)";
	if (check->precision > ft_strlen(s) || check->precision < 0)
		check->precision = ft_strlen(s);
	if (check->minus == 0)
	{
		w = check->width - check->precision;
		ft_print_space(' ', check, w);
		ft_putstr(s, check->precision, check);
	}
	if (check->minus == 1)
	{
		ft_putstr(s, check->precision, check);
		w = check->width - check->precision;
		ft_print_space(' ', check, w);
	}
}

void	ft_percent(t_list *check)
{
	if (check->minus == 1)
	{
		ft_putchar('%');
		check->length++;
		ft_print_space(' ', check, (check->width - 1));
	}
	else
	{
		if (check->zero == 1)
		{
			ft_print_space('0', check, (check->width - 1));
			ft_putchar('%');
			check->length++;
		}
		else
		{
			ft_print_space(' ', check, (check->width - 1));
			ft_putchar('%');
			check->length++;
		}
	}
}

int	ft_ptr_len(unsigned long pointer)
{
	int	i;

	i = 0;
	while (pointer != 0)
	{
		pointer = pointer / 16;
		i++;
	}
	return (i);
}

void    ft_unl_to_hex(unsigned long value, t_list *check)
{
    unsigned long 	hex;
	char			symbol;
		
	hex = 0;
	if (!value)
		return ;
	else
	{
		hex = value % 16;
		ft_unl_to_hex(value / 16, check);
	}
	if (hex > 9)
	{
		symbol = 'a' + (hex - 10);
        ft_putchar(symbol);
		check->length++;
	}
	else
	{
		symbol = hex + '0';
        ft_putchar(symbol);
		check->length++;
	}
}

void	ft_print_zero(char c, int len, t_list *check)
{
	while (len > 0)
	{
		write(1, &c, 1);
		check->length++;
		len--;
	}
}

void	ft_pointer(t_list *check)
{
	unsigned long	ptr;
	int				len;

	check->str++;
	ptr = va_arg(check->arguments, unsigned long);
	len = ft_ptr_len(ptr);
	if (check->precision > len)
	{
		write(1, "0x", 2);
		ft_print_zero('0', (check->precision - len), check);
	}

	ft_unl_to_hex(ptr, check);
}

void	ft_process_format(t_list *check)
{
	if (check->type == 1)
		ft_char(check);
	if (check->type == 2)
		ft_string(check);
	if (check->type == 3)
		ft_pointer(check);
	if (check->type == 7)
		ft_percent(check);
}

void	ft_check_format(t_list *check)
{
	ft_clean_flags(check);
	check->str++; // move from % to the next character
	ft_parse_flags(check);
	ft_parse_width(check);
	ft_parse_precision(check);
	ft_detect_format(check);
	ft_process_format(check);
}

int	ft_printf(const char *format, ...)
{
	t_list		*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (list == NULL)
		return (0);
	va_start(list->arguments, format);
	list->str = format;
	while (*list->str)
	{
		while (*list->str && *list->str != '%')
		{
			ft_putchar(*list->str);
			list->length++;
			list->str++;
		}
		if (*list->str && *list->str == '%')
			ft_check_format(list);
	}
	//printf("\nlength is: %d\n", list->length);
	va_end(list->arguments);
	free(list);
	return (list->length);
}

int main()
{

	int *a;
    int result;
	int my_result;
	// int b = 0;
    // int *int_pointer;
    // int_pointer = &a;
    // void *void_pointer;
    // char *char_pointer = NULL;
	my_result = ft_printf("%.16p", a);
    printf("\n");
    result = printf("%.16p", a);

	//printf("%p\n", void_pointer);
    // printf("\n");
	// ft_printf("%p\n", int_pointer);

	// int kek = 0, lol = 0;

	// printf("\n Проверка вывода \n\n");

	// kek = ft_printf("1.my_printf: %c end\n", 'o');
	// lol = printf("2.or_printf: %c end\n", 'o');
	// printf("mylen: %d\noriglen: %d\n\n", kek, lol);

	// kek = ft_printf("1.my_printf: %2.5c end\n", 'q');
	// lol = printf("2.or_printf: %2.5c end\n", 'q');
	// printf("mylen: %d\noriglen: %d\n\n", kek, lol);

	// kek = ft_printf("1.my_printf: %-4c end\n", 'q');
	// lol = printf("2.or_printf: %-4c end\n", 'q');
	// printf("mylen: %d\noriglen: %d\n\n", kek, lol);

	// kek = ft_printf("1.my_printf: %c end\n", 'q');
	// lol = printf("2.or_printf: %c end\n", 'q');
	// printf("mylen: %d\noriglen: %d\n\n", kek, lol);

	// kek = ft_printf("1.my_printf: %-*c end\n", 7, 'q');
	// lol = printf("2.or_printf: %-*c end\n", 7, 'q');
	// printf("mylen: %d\noriglen: %d\n\n", kek, lol);

	// kek = ft_printf("1.my_printf: %*c end\n", 5, 'q');
	// lol = printf("2.or_printf: %*c end\n", 5, 'q');
	// printf("mylen: %d\noriglen: %d\n\n", kek, lol);

	// kek = ft_printf("1.my_printf: %*c %c end\n", 5, 'q', 'w');
	// lol = printf("2.or_printf: %*c %c end\n", 5, 'q', 'w');
	// printf("mylen: %d\noriglen: %d\n\n", kek, lol);

	// kek = ft_printf("1.my_printf: %*c %-*c end\n", 5, 'q', 3, 'w');
	// lol = printf("2.or_printf: %*c %-*c end\n", 5, 'q', 3, 'w');
	// printf("mylen: %d\noriglen: %d\n\n", kek, lol);

	return (0);
}



if (width > pre)
{
	if (pre > strlen)
	{
		if (dot == 1 && pre == 0)
		else if (dot == 1 && pre != 0)
		else if (dot == 0)
	}
	else
	{
		if (dot == 1 && pre == 0)
		else if (dot == 1 && pre != 0)
		else if (dot == 0)
	}
}
else 
{

}