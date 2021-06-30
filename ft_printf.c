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
			flags->minus = 1;
		if (*flags->str == '0')
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
	if (*list->str == '.')
	{
		list->str = list->str++;
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
				list->precision = list->precision * 10 + (list->precision - '0');
				list->str++;
			}
		}
	}
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

void	ft_process_char(t_list *check)
{
	char c;

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

void	ft_process_format(t_list *check)
{
	if (check->type == 1)
		ft_process_char(check);
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
	printf("\nlength is: %d\n", list->length);
	va_end(list->arguments);
	free(list);
	return (list->length);
}

int	main()
{
	int a;
	const char	*z = "So%cme";
	//a = ft_printf(z);
	printf("\n");
	char c = 'X';
	ft_printf("%10c", c);
	return (0);
}