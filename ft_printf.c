//#include <stdio.h> // delete later
#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_putchars_fd(char c, int n)
{
	int	count;

	count = 0;
	while (count < n)
	{
		write(1, &c, 1);
		count++;
	}
	return (count);
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

int	ft_strlen(char *s)
{
	int	i;

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
	clean->zero = ' ';
	clean->star = 0;
	clean->sign = 0;
	clean->precision = -1;
}

void	ft_parse_flags(t_list *flags)
{
	while (*flags->str == '0' || *flags->str == '-')
	{
		if (*flags->str == '-')
		{
			flags->minus = 1;
			flags->str++;
		}
		if (*flags->str == '0')
		{
			flags->zero = '0';
			flags->str++;
		}
	}
	if (flags->minus == 1)
		flags->zero = ' ';
}

void	ft_parse_precision(t_list *list)
{
	list->str++;
	if (*list->str == '*')
	{
		list->precision = va_arg(list->arguments, int);
		if (list->precision < 0)
			list->precision = -1;
		list->str++;
		return ;
	}
	list->precision = ft_atoi(list->str);
	while (*list->str >= '0' && *list->str <= '9')
		list->str++;
}

void	ft_parse_width(t_list *flags)
{
	if (*flags->str == '*')
	{
		flags->width = va_arg(flags->arguments, int);
		flags->str++;
		if (flags->width < 0)
		{
			flags->width = flags->width * (-1);
			flags->minus = 1;
			flags->zero = ' ';
		}
		if (*flags->str == '.')
			ft_parse_precision(flags);
		return ;
	}
	flags->width = ft_atoi(flags->str);
	while (*flags->str >= '0' && *flags->str <= '9')
		flags->str++;
	if (*flags->str == '.')
		ft_parse_precision(flags);
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

void	ft_putstr(const char *s, int len, t_list *check)
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
		w = ft_strlen(s);
	else
		w = check->precision;
	if (check->minus == 0)
		ft_print_zero(check->zero, check->width - w, check);
	ft_putstr(s, w, check);
	check->str++;
	if (check->minus == 1)
		ft_print_space(' ', check, check->width - w);
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
		if (check->zero == '0')
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
	check->str++;
}

int	ft_ptr_len(unsigned long pointer)
{
	int	i;

	i = 0;
	if (pointer == 0)
		return (1);
	while (pointer != 0)
	{
		pointer = pointer / 16;
		i++;
	}
	return (i);
}

void    ft_unl_to_hex(unsigned long value, t_list *check)
{
	if (value / 16 != 0)
		ft_unl_to_hex(value / 16, check);
	if ((value % 16) > 9)
	{
		ft_putchar('a' + (value % 16) - 10);
		check->length++;
	}
	else
	{
        ft_putchar((value % 16) + '0');
		check->length++;
	}
}

void	ft_print_pointer(t_list *check)
{
	if (check->minus == 1)
	{
		ft_putstr("0x", 2, check);
		check->length += ft_putchars_fd('0', check->precision);
		check->length += ft_putchars_fd(' ', (check->width - check->precision - 2));
	}
	else
	{
		check->length += ft_putchars_fd(' ', (check->width - check->precision - 2));
		ft_putstr("0x", 2, check);
		check->length += ft_putchars_fd('0', check->precision);
	}
}

void	ft_print_zero_pointer(t_list *check)
{
	if (check->minus == 0)
	{
		check->length += ft_putchars_fd(' ', (check->width - 3));
		ft_putstr("0x0", 3, check);
	}
	else if (check->minus == 1)
	{
		ft_putstr("0x0", 3, check);
		check->length += ft_putchars_fd(' ', (check->width - 3));
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
		check->length += ft_putchars_fd(' ', (check->width - p_len - 2));
	else
		check->length += ft_putchars_fd(' ', (check->width - len - 2));
	ft_putstr("0x", 2, check);
	check->length += ft_putchars_fd('0', (check->precision - p_len));
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
		check->length += ft_putchars_fd('0', (check->width - p_len - 2));
		ft_unl_to_hex(ptr, check);
	}
	else
	{
		check->length += ft_putchars_fd(' ', (check->width - len - 2));
		ft_putstr("0x", 2, check);
		check->length += ft_putchars_fd('0', (check->precision - p_len));
		ft_unl_to_hex(ptr, check);
	}
}

int	ft_get_p_value(unsigned long value, t_list *check)
{
	int i;

	i = 0;
	if (value / 16 != 0)
			i += ft_get_p_value(value / 16, check);
	if ((value % 16) > 9)
		ft_putchar('a' + (value % 16) - 10);
	else
		ft_putchar((value % 16) + '0');
	i++;
	return (i);
}

void	ft_print_p(unsigned long ptr, int len, t_list *check)
{
	int	temp_len;

	temp_len = 0;
	if (check->minus == 0)
	{
		if (check->zero == '0')
			ft_printnmnz(ptr, len, check);
		else
			ft_print_pnmz(ptr, len, check);
	}
	else if (check->minus == 1)
	{
		ft_putstr("0x", 2, check);
		temp_len += ft_putchars_fd('0', (check->precision - len));
		//check->length += ft_putchars_fd('0', (check->precision - len));
		//ft_unl_to_hex(ptr, check);??
		temp_len += ft_get_p_value(ptr, check);
		check->length += temp_len;
		check->length += ft_putchars_fd(' ', (check->width - 2 - temp_len));
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
		check->str++;
		return ;
	}
	if (ptr == 0)
	{
		ft_print_zero_pointer(check);
		check->str++;
		return ;
	}
	len = ft_ptr_len(ptr);
	ft_print_p(ptr, len, check);
	check->str++;
}

void	ft_print_hex(unsigned int value, t_list *check)
{
	if (value / 16 != 0)
		ft_print_hex(value / 16, check);
	if ((value % 16) > 9)
	{
		if (check->hex_type == 'x')
			ft_putchar('a' + (value % 16) - 10);
		else
			ft_putchar('A' + (value % 16) - 10);
		check->length++;
	}
	else
	{
        ft_putchar((value % 16) + '0');
		check->length++;
	}
}

void	ft_hex(unsigned int hex, t_list *check, int len, int x_len)
{
	if (check->minus == 0)
	{
		if (check->precision >= 0)
		{
			check->length += ft_putchars_fd(' ', (check->width - len));
			check->length += ft_putchars_fd('0', (len - x_len));
			ft_print_hex(hex, check);
		}
		else
		{
			check->length += ft_putchars_fd(check->zero, (check->width - len));
			ft_print_hex(hex, check);
		}
	}
	else
	{
		check->length += ft_putchars_fd('0', (len - x_len));
		ft_print_hex(hex, check);
		check->length += ft_putchars_fd(' ', (check->width - len));
	}
}

void	ft_handle_x(t_list *check)
{
	unsigned int	x;
	int				len;
	int				x_len;

	x = va_arg(check->arguments, unsigned int);
	if (check->precision == 0 && x == 0)
	{
		check->length += ft_putchars_fd(' ', check->width);
		check->str++;
		return ;
	}
	x_len = ft_ptr_len(x);
	if (check->precision > x_len)
		len = check->precision;
	else
		len = x_len;
	ft_hex(x, check, len, x_len);
	check->str++;
}

int	ft_unsigned_len(unsigned int value)
{
	int	count;

	count = 0;
	while (value / 10 != 0)
	{
		count++;
		value /= 10;
	}
	count++;
	return (count);
}

void	ft_print_un(unsigned int value, t_list *check)
{
	if (value / 10 != 0)
		ft_print_un(value / 10, check);
	if ((value % 10) > 9)
	{
		ft_putchar('a' + (value % 10) - 10);
		check->length++;
	}
	else
	{
        ft_putchar((value % 10) + '0');
		check->length++;
	}
}

void	ft_print_unsigned(unsigned int value, int len, int uns_len, t_list *check)
{
	if (check->minus == 0)
	{
		if (check->precision >= 0)
		{
			check->length += ft_putchars_fd(' ', (check->width - len));
			check->length += ft_putchars_fd('0', len - uns_len);
			ft_print_un(value, check);
		}
		else
		{
			check->length += ft_putchars_fd(check->zero, check->width - len);
			ft_print_un(value, check);
		}
	}
	else
	{
		check->length += ft_putchars_fd('0', (len - uns_len));
		ft_print_un(value, check);
		check->length += ft_putchars_fd(' ', (check->width - len));
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
		check->length += ft_putchars_fd(' ', check->width);
		check->str++;
		return ;
	}
	uns_len = ft_unsigned_len(value);
	if (check->precision > uns_len)
		len = check->precision;
	else
		len = uns_len;
	ft_print_unsigned(value, len, uns_len, check);
	check->str++;
}

int	ft_int_len(int value)
{
	int	i;

	i = 0;
	if (value == 0)
		return (1);
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
	int				x;
	unsigned int	value_int;
	
	x = 0;
	value_int = ft_change_sign(value);
	if (value_int / 10 != 0)
		ft_print_int(value_int / 10, check);
	if (value_int % 10 <= 9)
	{
		ft_putchar(value_int % 10 + '0');
		check->length++;
	}
	else
	{
		ft_putchar(value_int % 10 + 'a');
		check->length++;
	}
}

void	ft_p_i(int value, t_list *check, int len, int int_len)
{
	if (check->precision >= 0)
	{
		check->length += ft_putchars_fd(' ', check->width - len - check->sign);
		check->length += ft_putchars_fd('-', check->sign);
		check->length += ft_putchars_fd('0', len - int_len);
		ft_print_int(value, check);
	}
	else
	{
		if (check->zero == ' ')
			check->length += ft_putchars_fd(' ', (check->width - int_len - check->sign));
		check->length += ft_putchars_fd('-', check->sign);
		if (check->zero == '0')
			check->length += ft_putchars_fd('0', check->width - int_len - check->sign);
		ft_print_int(value, check);
	}
}

void	ft_print_integer(int value, t_list *check, int len, int int_len)
{
	if (check->minus == 0)
		ft_p_i(value, check, len, int_len);
	else
	{
		check->length += ft_putchars_fd('-', check->sign);
		check->length += ft_putchars_fd('0', len - int_len);
		ft_print_int(value, check);
		check->length += ft_putchars_fd(' ', check->width - len - check->sign);
	}
}

int	ft_print_char(char s, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		ft_putchar(s);
		len--;
		i++;
	}
	return (i);
}

void	ft_int(t_list *check)
{
	int	len;
	int	int_len;
	int	value;
	
	value = va_arg(check->arguments, int);
	if (check->precision == 0 && value == 0)
	{
		check->length += ft_print_char(' ', check->width);
		check->str++;
		return ;
	}
	int_len = ft_int_len(value);
	if (value < 0)
		check->sign = 1;
	if (check->precision > int_len)
		len = check->precision;
	else
		len = int_len;
	ft_print_integer(value, check, len, int_len);
	check->str++;
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
	ft_detect_format(check);
	if (check->type)
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
