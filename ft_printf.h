#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

// typedef struct s_info
// {
// 	int		sign;
// 	char	zero;
// 	int		star;
// 	int		width;
// 	int		precision;
// 	char	specifier;
// 	int		d_s;
// }				t_info;

typedef struct s_list
{
	const char	*str;
	va_list		arguments;
	int			type;
	int			width;
	int			minus;
	char		zero;
	int			precision;
	int			star;
	int			length;
	int			sign;
	char		hex_type;
}				t_list;

int	ft_printf(const char *format, ...);

#endif