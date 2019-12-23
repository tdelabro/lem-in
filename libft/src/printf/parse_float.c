/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:34:29 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 16:53:27 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../inc/ft_printf.h"

/*
** Printing of nan is hadled apart because it's not influenced by prec or
** flags.
*/

static int	ft_nan(char *buff, t_format *format)
{
	int ret;

	ret = 0;
	if (format->f_l == FALSE)
		while (format->fi_w > 3 && ret < format->fi_w - 3)
			ret += ft_buff(buff, ' ', 0);
	ret += ft_buff(buff, 'n', 0);
	ret += ft_buff(buff, 'a', 0);
	ret += ft_buff(buff, 'n', 0);
	if (format->f_l == TRUE)
		while (ret < format->fi_w)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Printint infinity and zero value (for f and e conv)
*/

static int	ft_getparse(const short n, char *buff, t_format *format)
{
	int	ret;

	ret = 0;
	if (n == 1 || n == -1)
	{
		ret += ft_buff(buff, '0', 0);
		if (!(format->prec == 0 && format->f_h == FALSE))
			ret += ft_buff(buff, '.', 0);
		while (format->prec-- > 0)
			ret += ft_buff(buff, '0', 0);
		if (format->conv == 'e')
		{
			ret += ft_buff(buff, 'e', 0);
			ret += ft_buff(buff, '+', 0);
			ret += ft_buff(buff, '0', 0);
			ret += ft_buff(buff, '0', 0);
		}
	}
	if (n == 2 || n == -2)
	{
		ret += ft_buff(buff, 'i', 0);
		ret += ft_buff(buff, 'n', 0);
		ret += ft_buff(buff, 'f', 0);
	}
	return (ret);
}

/*
** For Infinity and zero value.
** Take care of everything to be printed before and after the real value, due to
** field width and display flags (+- 0)
*/

static int	ft_fillparse(const short n, int len, char *buff, t_format *frmt)
{
	int		ret;
	t_bool	mod;

	ret = 0;
	mod = (n < 0 || frmt->f_si == TRUE || frmt->f_sp == TRUE) ? 1 : 0;
	(frmt->conv == 'e') ? mod += 4 : 1;
	frmt->f_z = (frmt->f_z == TRUE && frmt->f_l == FALSE) ? 1 : 0;
	if (frmt->f_l == TRUE || (n * n == 1 && frmt->f_z == TRUE))
	{
		ret += ft_mod(frmt, buff, (n < 0) ? 1 : 0);
		if (n * n == 1 && frmt->f_z == TRUE)
			while (frmt->fi_w > len && ret < frmt->fi_w - len)
				ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (frmt->fi_w > len + (int)mod && ret < frmt->fi_w - len - (int)mod)
			ret += ft_buff(buff, ' ', 0);
		ret += ft_mod(frmt, buff, (n < 0) ? 1 : 0);
	}
	ret += ft_getparse(n, buff, frmt);
	if (frmt->f_l == TRUE)
		while (ret < frmt->fi_w)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Twins double/long double funtions that check for the three float values that
** will be printed without processing the Dragon4 algorithm :
** · +/- zero
** · +/- infinity
** · not a number
*/

int			ft_parse_ldbl(const long double n, t_format *format, char *buff)
{
	int	len;
	int	ret;

	ret = 0;
	len = (format->prec == 0 && format->f_h == FALSE) ? 1 : 2 + format->prec;
	if (n == 0 && ((unsigned char*)&n)[9] & 0x80)
		ret = ft_fillparse(-1, len, buff, format);
	else if (n == 0 && !(((unsigned char*)&n)[9] & 0x80))
		ret = ft_fillparse(1, len, buff, format);
	else if (n == INFINITY)
		ret = ft_fillparse(2, 3, buff, format);
	else if (n == -INFINITY)
		ret = ft_fillparse(-2, 3, buff, format);
	else if ((((unsigned char*)&n)[9] & 0x7f) == 0x7f \
									&& (((unsigned char*)&n)[8] & 0xff) == 0xff)
		ret = ft_nan(buff, format);
	else
		return (0);
	return (ret);
}

int			ft_parse_dbl(const double n, t_format *format, char *buff)
{
	int	len;
	int	ret;

	ret = 0;
	len = (format->prec == 0 && format->f_h == FALSE) ? 1 : 2 + format->prec;
	if (n == 0 && (0x8000000000000000 & *(uint64_t*)&n))
		ret = ft_fillparse(-1, len, buff, format);
	else if (n == 0 && !((0x8000000000000000 & *(uint64_t*)&n)))
		ret = ft_fillparse(1, len, buff, format);
	else if (n == INFINITY)
		ret = ft_fillparse(2, 3, buff, format);
	else if (n == -INFINITY)
		ret = ft_fillparse(-2, 3, buff, format);
	else if ((0x7ff0000000000000 & *(uint64_t*)&n) == 0x7ff0000000000000)
		ret = ft_nan(buff, format);
	else
		return (0);
	return (ret);
}
