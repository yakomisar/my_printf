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
	char		hex_type;
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
	{
		format = 6;
		if (*check->str == 'x')
			check->hex_type = 'x';
		else
			check->hex_type = 'X';
	}
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

void	ft_print_pointer(t_list *check)
{
	if (check->minus == 1)
	{
		ft_putstr("0x", 2, check);
		ft_print_zero('0', check->precision, check);
		ft_print_space(' ', check, (check->width - check->precision - 2));
	}
	else
	{
		ft_print_space(' ', check, (check->width - check->precision - 2));
		ft_putstr("0x", 2, check);
		ft_print_zero('0', check->precision, check);
	}
}

void	ft_print_zero_pointer(t_list *check)
{
	if (check->minus == 0)
	{
		ft_print_space(' ', check, (check->width - 3));
		ft_putstr("0x0", 3, check);
	}
	else if (check->minus == 1)
	{
		ft_print_space("0x0", check, 3);
		ft_print_space(' ', check, (check->width - 3));
	}
}

void	ft_print_pnmz(unsigned long ptr, int p_len, t_list *check)
{
	int	len;

	if (check->precision > p_len)
		len = check->precision;
	else
		len = p_len;
	if (check->precision == -1)
		ft_print_space(' ', check, (check->width - p_len - 2));
	else
		ft_print_space(' ', check, (check->width - len - 2));
	ft_putstr("0x", 2, check);
	ft_print_space('0', check, (check->precision - p_len));
	ft_unl_to_hex(ptr, check);
}

void	ft_printnmnz(unsigned long ptr, int p_len, t_list *check)
{
	int	len;

	if (check->precision > 0)
		len = check->precision;
	else
		len = 0;
	if (check->precision == -1)
	{
		ft_putstr("0x", 2, check);
		ft_print_zero('0', (check->width - p_len - 2), check);
		ft_unl_to_hex(ptr, check);
	}
	else
	{
		ft_print_space(' ', check, (check->width - len - 2));
		ft_putstr("0x", 2, check);
		ft_print_space('0', check, (check->precision - p_len));
		ft_unl_to_hex(ptr, check);
	}
}

void	ft_print_p(unsigned long ptr, int len, t_list *check)
{
	if (check->minus == 0)
	{
		if (check->zero == 1)
			ft_print_pnmz(ptr, len, check);
		else
			ft_printnmnz(ptr, len, check);
	}
	else if (check->minus == 1)
	{
		ft_putstr("0x", 2, check);
		ft_print_zero('0', (check->precision - len), check);
		ft_unl_to_hex(ptr, check);
		ft_print_space(' ', check, (check->width - check->precision - len - 2));
	}
}

void	ft_pointer(t_list *check)
{
	unsigned long	ptr;
	int				len;

	ptr = va_arg(check->arguments, unsigned long);
	if (check->precision >= 0 && ptr == 0)
	{
		ft_print_pointer(check);
		return ;
	}
	if (ptr == 0)
	{
		ft_print_zero_pointer(check);
		return ;
	}
	len = ft_ptr_len(ptr);
	ft_print_p(ptr, len, check);
}

void	ft_print_hex(unsigned int value, t_list *check)
{
	unsigned int 	hex;
	
	hex = 0;
	if (!hex)
		return ;
	else
	{
		hex = value % 16;
		ft_print_hex(value / 16, check);
	}
	if (hex > 9)
	{
		if (check->hex_type == 'x')
		{
        	ft_putchar('a' + hex - 10);
			check->length++;	
		}
		else
		{
        	ft_putchar('A' + hex - 10);
			check->length++;
		}
	}
	else
	{
        ft_putchar(hex + '0');
		check->length++;
	}
}

void	ft_hex(unsigned int hex, t_list *check, int p_r, int len)
{
	if (check->minus == 0)
	{
		if (check->precision >= 0)
		{
			ft_print_space(' ', check, (check->width - p_r));
			ft_print_zero('0', (p_r - len), check);
			ft_print_hex(hex, check);
		}
		else
		{
			ft_print_symbol(' ', (check->width - p_r), check);
			ft_print_hex(hex, check);
		}
	}
	else
	{
		ft_print_space('0', check, (p_r - len));
		ft_print_hex(hex, check);
		ft_print_space(' ', check, (check->width - len));
	}
}

void	ft_handle_x(t_list *check)
{
	unsigned int	x;
	int				len;
	int				p_r;

	check->str++;
	x = va_arg(check->arguments, unsigned int);
	if (check->precision == 0 && x == 0)
	{
		ft_print_space(' ', check, check->width);
		return ;
	}
	len = ft_ptr_len(x);
	if (check->precision > len)
		p_r = check->precision;
	else
		p_r = len;
	ft_hex(x, check, p_r, len);
}

int	ft_unsigned_len(unsigned int value)
{
	int	i;

	i = 0;
	while (value != 0)
	{
		value = value / 10;
		i++;
	}
	return (i);
}

void	ft_print_un(unsigned int value, t_list *check)
{
	unsigned int 	uns;
	
	uns = 0;
	if (!uns)
		return ;
	else
	{
		uns = value % 10;
		ft_print_un(value / 10, check);
	}
	if (uns > 9)
	{
		ft_putchar('a' + uns - 10);
		check->length++;
	}
	else
	{
        ft_putchar(uns + '0');
		check->length++;
	}
}

void	ft_print_unsigned(unsigned int value, int uns_len, int len, t_list *check)
{
	if (check->minus == 0)
	{
		if (check->precision >= 0)
		{
			ft_print_space(' ', check, (check->width - uns_len));
			ft_print_zero('0', uns_len - len, check);
			ft_print_un(value, check);
		}
		else
		{
			ft_print_symbol(' ', check->width - uns_len, 1);
			ft_print_un(value, check);
		}
	}
	else
	{
		ft_print_space('0', check, (uns_len - len));
		ft_print_un(value, check);
		ft_print_space(' ', check, (check->width - uns_len));
	}
}

void	ft_unsigned(t_list *check)
{
	unsigned int	value;
	int				uns_len;
	int				len;

	value = va_arg(check->arguments, unsigned int);
	if (check->precision == 0 && value == 0)
	{
		ft_print_space(' ', check, check->width);
		return ;
	}
	len = ft_unsigned_len(value);
	if (check->precision > len)
		uns_len = check->precision;
	else
		uns_len = len;
	ft_print_unsigned(value, uns_len, len, check);
}

int	ft_int_len(int value)
{
	int	i;

	i = 0;
	while (value != 0)
	{
		value = value / 10;
		i++;
	}
	return (i);
}

int	ft_change_sign(int value)
{
	int	m;

	if (value >= 0)
		m = value;
	else
		m = -value;
	return (m);
}

void	ft_print_int(int value, t_list *check)
{
	int 	x;
	int		value_int;
	
	x = 0;
	value_int = ft_change_sign(value);
	if (!x)
		return ;
	else
	{
		x = value_int % 10;
		ft_print_int(value_int / 10, check);
	}
	if (x > 9)
	{
		ft_putchar('a' + x - 10);
		check->length++;
	}
	else
	{
        ft_putchar(x + '0');
		check->length++;
	}
}

void	ft_p_i(int value, t_list *check, int len, int int_len, int sign)
{
	if (check->precision >= 0)
	{
		ft_print_space(' ', check, check->width - len - sign);
		ft_print_symbol('-', sign, check);
		ft_print_zero('0', len - int_len, check);
		ft_print_int(value, check);
	}
	else
	{
		if (check->zero == 0)
			ft_print_space(' ', check, (check->width - int_len - sign));
		ft_print_symbol('-', sign, check);
		if (check->zero == 1)
			ft_print_zero('0', (check->width - int_len - sign), check);
		ft_print_int(value, check);
	}
}

void	ft_print_integer(int value, t_list *check, int len, int int_len, int sign)
{
	if (check->minus == 0)
		ft_print_integer_2(value, check, len, int_len, sign);
	else
	{
		ft_print_symbol('-', sign, check);
		ft_print_zero('0', len - int_len, check);
		ft_print_int(value, check);
		ft_print_space(' ', check, check->width - len - sign);
	}
}

void	ft_int(t_list *check)
{
	int	len;
	int	int_len;
	int	value;
	int	sign;

	value = va_arg(check->arguments, int);
	if (check->precision == 0 && value == 0)
	{
		ft_print_space(' ', check, check->width);
		return ;
	}
	int_len = ft_int_len(value);
	if (value < 0)
		sign = 1;
	if (check->precision > len)
		len = check->precision;
	else
		len = int_len;
	ft_print_integer(value, check, len, int_len, sign);	
}

void	ft_process_format(t_list *check)
{
	if (check->type == 1)
		ft_char(check);
	if (check->type == 2)
		ft_string(check);
	if (check->type == 3)
		ft_pointer(check);
	if (check->type == 4)
		ft_int(check);
	if (check->type == 5)
		ft_unsigned(check);
	if (check->type == 6)
		ft_handle_x(check);
	if (check->type == 7)
		ft_percent(check);
}

void	ft_check_format(t_list *check)
{
	ft_clean_flags(check);
	check->str++;
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
	va_end(list->arguments);
	free(list);
	return (list->length);
}

int main()
{

	int *a;
    int result;
	int my_result;
	my_result = ft_printf("%.16p", a);
    printf("\n");
    result = printf("%.16p", a);
	return (0);
}
