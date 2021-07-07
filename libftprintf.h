#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_info
{
	int		sign;
	char	zero;
	int		star;
	int		width;
	int		precision;
	char	specifier;
	int		d_s;
}				t_info;

int				uns_howmanychars(unsigned int n, int base);

/*
** ft_printf.c
*/

t_info			init_flags(void);
int				ft_parse(va_list argptr, char *s);
int				ft_printf(const char *s, ...);

/*
** ft_parse_flags.c
*/

int				ft_parse_width(char *s, t_info *flags, va_list argptr);
int				ft_parse_pricision(char *s, t_info *flags, va_list argptr);
int				ft_parse_signes(char *s, t_info *flags);
int				ft_parse_flags(char *s, t_info *flags, va_list argptr);

/*
** my_gang.c
*/

int				ft_putchars_fd(char c, int n, int fd);
int				ft_putnstr_fd(const char *s, int n, int fd);
int				ft_isfromset(char *s, char c);
int				howmanychars(int n, int base);

/*
** my_gang2.c
*/

unsigned int	ft_make_uns(int n);
int				ft_putnbr_base_fd(int n, int base, int reg, int fd);
int				ft_putnbr_long_base_fd(unsigned int n, int base, \
				int reg, int fd);

/*
** my_gang3.c
*/

int				ft_isspace(char c);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			ft_putchar_fd(char c, int fd);
size_t			ft_strlen(const char *s);

/*
** print_c_s.c
*/

int				ft_print_c(t_info flags, va_list argptr);
int				ft_print_s(t_info flags, va_list argptr);

/*
** print_p.c
*/

int				put_p(unsigned long p, t_info flags);
int				put_p_str(t_info flags);
int				put_p_null_prec(t_info flags);
int				ft_print_p(t_info flags, va_list argptr);

/*
** print_d.c
*/

int				ft_print_d_help_2(int d, t_info flags, int fulllen, int len);
int				ft_print_d_help(int d, t_info flags, int fulllen, int len);
int				ft_print_d(t_info flags, va_list argptr);

/*
** print_d_help.c
*/

int				ft_putnbr_llll_base_fd(unsigned long n, int base, \
				int reg, int fd);
int				howmanychars_long(unsigned long n, int base);
int				put_p_help(unsigned long p, t_info flags);
int				put_p_help_2(unsigned long p, t_info flags);

/*
** print_u.c
*/

int				uns_howmanychars(unsigned int n, int base);
int				ft_print_u_help(unsigned int u, t_info flags, \
				int fulllen, int len);
int				ft_print_u(t_info flags, va_list argptr);
int				ft_print_persent(t_info flags);

/*
** print_x.c
*/

int				ft_print_x_help(unsigned int x, t_info flags, \
				int fulllen, int len);
int				ft_print_x(t_info flags, va_list argptr);
int				ft_print_xx_help(unsigned int x, t_info flags, \
				int fulllen, int len);
int				ft_print_xx(t_info flags, va_list argptr);

/*
** ft_go_print.c
*/

int				ft_go_print_them_tiger(t_info flags, va_list argptr);

#endif