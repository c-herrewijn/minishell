/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 20:30:20 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/02/08 16:12:23 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
validates the format
returns the number of formats, or -1 in case the format string is invalid
a '%' sign should be followed by a format char 
2 consequtive '%%' chars in the format string are printed '%'
*/
static int	format_valid(const char *format_str, char *format_chars)
{
	int	format_count;
	int	i;

	if (!format_str || !format_chars)
		return (-1);
	i = 0;
	format_count = 0;
	while (format_str[i])
	{
		if (format_str[i] == '%')
		{
			if (format_str[i + 1] && ft_strchr(format_chars, format_str[i + 1]))
			{
				i++;
				format_count++;
			}
			else if (format_str[i + 1] == '%')
				i++;
			else
				return (-1);
		}
		i++;
	}
	return (format_count);
}

static void	print_va_arg(const char format_char, int *print_len, va_list ap)
{
	char					c;

	if (format_char == 'c')
	{
		c = va_arg(ap, int);
		*print_len += write(1, &c, 1);
	}
	if (format_char == 's')
		printf_putstr(va_arg(ap, char *), print_len);
	if (format_char == 'p')
	{
		*print_len += write(1, "0x", 2);
		printf_putunsignedhex(va_arg(ap, unsigned long long int),
			print_len, 'l');
	}
	if (format_char == 'd' || format_char == 'i')
		printf_putnbr(va_arg(ap, int), print_len);
	if (format_char == 'u')
		printf_putunsnbr(va_arg(ap, unsigned int), print_len);
	if (format_char == 'x')
		printf_putunsignedhex(va_arg(ap, unsigned int), print_len, 'l');
	if (format_char == 'X')
		printf_putunsignedhex(va_arg(ap, unsigned int), print_len, 'u');
	if (format_char == '%')
		*print_len += write(1, "%", 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*format_chars;
	int		print_len;

	va_start(ap, format);
	format_chars = "cspdiuxX";
	print_len = 0;
	if (format_valid(format, format_chars) < 0)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			print_va_arg(*format, &print_len, ap);
		}
		else
			print_len += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (print_len);
}
