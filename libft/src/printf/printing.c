/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:24:46 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 16:48:22 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** All these function handle the printing of character before the real output,
** based on field width, prec, flags(#+- 0).
** Each one have a sligthy different functionment but the architecture remains.
** Shared subfunctions can be find in the printing_complement.c file.
*/

int	ft_pre_printing_dec(t_format *f, int len, char *buff,\
		t_bool sign)
{
	int		ret;
	t_bool	mod;
	int		tmp;

	ret = 0;
	f->f_z = (f->f_z == 1 && f->f_l == 0 && f->f_p == 0) ? 1 : 0;
	mod = (sign == 1 || f->f_si == TRUE || f->f_sp == TRUE) ? 1 : 0;
	tmp = (f->f_p == TRUE && f->prec > len) ? f->prec : len;
	if (f->f_z == TRUE || f->f_l == TRUE)
	{
		ret += ft_mod(f, buff, sign);
		while (f->f_z == TRUE && ret < f->fi_w - tmp)
			ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (f->fi_w > tmp + (int)mod && ret < f->fi_w - tmp - (int)mod)
			ret += ft_buff(buff, ' ', 0);
		if (f->f_z == FALSE)
			ret += ft_mod(f, buff, sign);
	}
	ret += ft_endzero(f, len, buff, tmp);
	return (ret);
}

int	ft_pre_printing_float(t_format *f, int len, t_bool sign)
{
	int		ret;
	t_bool	mod;
	int		tmp;
	char	buff[PFBUF];

	ret = 0;
	f->f_z = (f->f_z == 1 && f->f_l == 0) ? 1 : 0;
	mod = (sign == 1 || f->f_si == TRUE || f->f_sp == TRUE) ? 1 : 0;
	tmp = (f->f_p == TRUE && f->prec > len) ? f->prec : len;
	if (f->f_z == TRUE || f->f_l == TRUE)
	{
		ret += ft_mod(f, buff, sign);
		while (f->f_z == TRUE && ret < f->fi_w - tmp)
			ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (f->fi_w > tmp + (int)mod && ret < f->fi_w - tmp - (int)mod)
			ret += ft_buff(buff, ' ', 0);
		if (f->f_z == FALSE)
			ret += ft_mod(f, buff, sign);
	}
	ret += ft_endzero(f, len, buff, tmp);
	ft_buff(buff, '0', 1);
	return (ret);
}

int	ft_pre_printing_add(t_format *format, int len, char *buff)
{
	int		ret;
	int		tmp;

	ret = 0;
	format->f_z = (format->f_z == 1 && format->f_l == 0 && format->f_p == 0) \
																		? 1 : 0;
	tmp = (format->f_p == TRUE && format->prec > len) ? format->prec : len;
	if (format->f_z == TRUE || format->f_l == TRUE)
	{
		ret += ft_buff(buff, '0', 0);
		ret += ft_buff(buff, 'x', 0);
		while (format->f_z == TRUE && ret < format->fi_w - tmp)
			ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (format->fi_w > tmp + 2 && ret < format->fi_w - tmp - 2)
			ret += ft_buff(buff, ' ', 0);
		ret += ft_buff(buff, '0', 0);
		ret += ft_buff(buff, 'x', 0);
	}
	ret += ft_endzero(format, len, buff, tmp);
	return (ret);
}

int	ft_pre_printing_uhex(t_format *f, int len, char *bf, int tm)
{
	int	ret;

	ret = 0;
	if (f->f_z == TRUE || f->f_l == TRUE)
	{
		if (f->f_h == TRUE)
		{
			ret += ft_buff(bf, '0', 0);
			ret += (f->conv == 'x') ? ft_buff(bf, 'x', 0) : ft_buff(bf, 'X', 0);
		}
		while (f->f_z == TRUE && ret < f->fi_w - tm)
			ret += ft_buff(bf, '0', 0);
	}
	else
	{
		while (f->fi_w > tm + (f->f_h * 2) && ret < f->fi_w - tm - (f->f_h * 2))
			ret += ft_buff(bf, ' ', 0);
		if (f->f_h == TRUE)
		{
			ret += ft_buff(bf, '0', 0);
			ret += (f->conv == 'x') ? ft_buff(bf, 'x', 0) : ft_buff(bf, 'X', 0);
		}
	}
	ret += ft_endzero(f, len, bf, tm);
	return (ret);
}

int	ft_pre_printing_uoct(t_format *format, int len, char *buff, int tmp)
{
	int ret;

	ret = 0;
	if (format->f_z == TRUE || format->f_l == TRUE)
	{
		if (format->f_h == TRUE)
			ret += ft_buff(buff, '0', 0);
		while (format->f_z == TRUE && format->fi_w > tmp \
				&& ret < format->fi_w - tmp)
			ret += ft_buff(buff, '0', 0);
	}
	else
	{
		while (format->fi_w > tmp + (int)format->f_h \
			&& ret < format->fi_w - tmp - (int)format->f_h)
			ret += ft_buff(buff, ' ', 0);
		if (format->f_h == TRUE)
			ret += ft_buff(buff, '0', 0);
	}
	ret += ft_endzero(format, len, buff, tmp);
	return (ret);
}
