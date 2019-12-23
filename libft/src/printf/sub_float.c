/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:37:19 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 16:54:34 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../inc/ft_printf.h"

/*
** Those two pairs of function (bdbl/ldbl) initialize the Dragon4 algorithm
** needed values and then inject them into the good printing function according
** to the conv flag (e or f) and the value (value < -1 || value > 1).
*/

static int	ft_sndp_ldbl(t_hint *valnum, t_hint *valdenum, int *tab, \
				t_format *format)
{
	int ret;

	if (tab[3] == 1)
	{
		if (format->conv == 'e')
			ret = ft_getstr_supone_lde(valnum, valdenum, tab, format);
		else
			ret = ft_getstr_supone_ld(valnum, valdenum, tab, format);
	}
	else
	{
		if (format->conv == 'e')
			ret = ft_getstr_minone_lde(valnum, valdenum, tab, format);
		else
			ret = ft_getstr_minone_ld(valnum, valdenum, tab, format);
	}
	return (ret);
}

static int	ft_res_ldbl(long double n, t_format *format)
{
	t_hint	valnum;
	t_hint	valdenum;
	int		tab[4];

	tab[0] = ft_getfirstdigit_ldbl(n);
	ft_init_numdenum_ld(&valnum, &valdenum, n, tab[0]);
	tab[2] = (((unsigned char*)&n)[9] & 0x80) >> 7;
	tab[3] = (n >= 1 || n <= -1) ? 1 : 0;
	if (format->conv == 'e')
		tab[1] = 4 + ((format->f_p == 1) ? format->prec : 6) \
			+ ((tab[0] < 100) ? 2 : ft_lenint_base(tab[0], 10));
	else if (n >= 1 || n <= -1)
		tab[1] = (format->f_p == 1 && format->prec == 0) ?\
			1 + tab[0] : (2 + tab[0] + format->prec);
	else
		tab[1] = (format->prec == 0 && format->f_h == FALSE) ?\
			1 : (2 + format->prec);
	return (ft_sndp_ldbl(&valnum, &valdenum, tab, format));
}

static int	ft_sndp_dbl(t_bint *valnum, t_bint *valdenum, int *tab, \
				t_format *format)
{
	int ret;

	if (tab[3] == 1)
	{
		if (format->conv == 'e')
			ret = ft_getstr_supone_de(valnum, valdenum, tab, format);
		else
			ret = ft_getstr_supone_d(valnum, valdenum, tab, format);
	}
	else
	{
		if (format->conv == 'e')
			ret = ft_getstr_minone_de(valnum, valdenum, tab, format);
		else
			ret = ft_getstr_minone_d(valnum, valdenum, tab, format);
	}
	return (ret);
}

static int	ft_res_dbl(double n, t_format *format)
{
	t_bint	valnum;
	t_bint	valdenum;
	int		tab[4];

	tab[0] = ft_getfirstdigit_d((n < 0) ? -n : n);
	ft_init_numdenum_d(&valnum, &valdenum, n, tab[0]);
	tab[2] = (*(int64_t*)&n & 0x8000000000000000) >> 63;
	tab[3] = (n >= 1 || n <= -1) ? 1 : 0;
	if (format->conv == 'e')
		tab[1] = 4 + ((format->f_p == 1) ? format->prec : 6) \
			+ ((tab[0] < 100) ? 2 : ft_lenint_base(tab[0], 10));
	else if (n >= 1 || n <= -1)
		tab[1] = (format->f_p == 1 && format->prec == 0) ?\
			1 + tab[0] : (2 + tab[0] + format->prec);
	else
		tab[1] = (format->prec == 0 && format->f_h == FALSE) ?\
			1 : (2 + format->prec);
	return (ft_sndp_dbl(&valnum, &valdenum, tab, format));
}

/*
** This function extract the float argument from the va_list, parse it (for NAN,
** zero and infinity values) and inject it in the correct (dbl/ldbl) version of
** the Dragon4 algorithm.
*/

int			ft_sub_float(t_format *f, va_list args, char *buff)
{
	double		n;
	long double	m;
	int			ret;

	if (f->len_mod == L)
	{
		m = (long double)va_arg(args, long double);
		if (((unsigned char*)&m)[0] == 0 && ((unsigned char*)&m)[1] == 0 \
			&& ((unsigned char*)&m)[2] == 0 && ((unsigned char*)&m)[3] == 0 \
			&& ((unsigned char*)&m)[4] == 1 && ((unsigned char*)&m)[5] == 0 \
			&& ((unsigned char*)&m)[6] == 0 && ((unsigned char*)&m)[7] == 0)
			ret = ft_parse_ldbl(NAN, f, buff);
		else
			ret = ft_parse_ldbl(m, f, buff);
	}
	else
	{
		n = (double)va_arg(args, double);
		ret = ft_parse_dbl(n, f, buff);
	}
	if (ret == 0)
		ft_buff(buff, 0, 1);
	if (ret == 0)
		ret = (f->len_mod == L) ? ft_res_ldbl(m, f) : ft_res_dbl(n, f);
	return (ret);
}
