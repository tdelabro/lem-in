/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_txt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:28:50 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 16:37:21 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Function to be use if the conv instruction does not contain any valid
** conv symbol.
*/

int			ft_sub_unknown(t_format *format, va_list args, char *buff)
{
	int		ret;
	char	padd;

	if (args || !args)
		ret = 0;
	padd = (format->f_z == TRUE && format->f_l == FALSE) ? '0' : ' ';
	if (format->f_l == FALSE)
	{
		if (format->fi_w > 1)
			while (ret < format->fi_w - 1)
				ret += ft_buff(buff, padd, 0);
	}
	ret += ft_buff(buff, format->conv, 0);
	while (ret < format->fi_w)
		ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Handle the '%' conv.
*/

int			ft_sub_percent(t_format *format, va_list args, char *buff)
{
	char	padd;
	int		ret;

	if (args || !args)
		ret = 0;
	padd = (format->f_z == TRUE && format->f_l == FALSE) ? '0' : ' ';
	if (format->f_l == FALSE)
	{
		if (format->fi_w > 1)
			while (ret < format->fi_w - 1)
				ret += ft_buff(buff, padd, 0);
	}
	ret += ft_buff(buff, '%', 0);
	while (ret < format->fi_w)
		ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Handle the 'c' conv, character printing.
*/

int			ft_sub_char(t_format *format, va_list args, char *buff)
{
	char	c;
	int		ret;
	char	padd;

	c = va_arg(args, int);
	ret = 0;
	padd = (format->f_z == TRUE && format->f_l == FALSE) ? '0' : ' ';
	if (format->f_l == FALSE)
		if (format->fi_w > 1)
			while (ret < format->fi_w - 1)
				ret += ft_buff(buff, padd, 0);
	ret += ft_buff(buff, c, 0);
	if (format->f_l == TRUE)
		while (ret < format->fi_w)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Handle the 's' conv, string printing.
*/

static	int	ft_getstr(char *buff, char *str, t_bool prec, int precision)
{
	int	i;

	i = 0;
	while (str[i] && (prec == FALSE || (prec == TRUE && i < precision)))
	{
		ft_buff(buff, str[i], 0);
		i++;
	}
	return (i);
}

int			ft_sub_string(t_format *format, va_list args, char *buff)
{
	char	*str;
	char	padd;
	int		ret;
	int		tmp;

	str = va_arg(args, char*);
	ret = 0;
	if (str)
		!(str[0]) ? format->f_p = 0 : 1;
	padd = (format->f_z == TRUE && format->f_l == FALSE) ? '0' : ' ';
	tmp = (str == NULL) ? 6 : ft_strlen(str);
	if (format->f_l == FALSE)
	{
		tmp = (format->f_p == TRUE && format->prec < tmp) ? format->prec : tmp;
		while (tmp++ < format->fi_w)
			ret += ft_buff(buff, padd, 0);
	}
	ret += ft_getstr(buff, (str == NULL) ? "(null)" : str,\
											format->f_p, format->prec);
	if (format->f_l == TRUE)
		while (ret < format->fi_w)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}
