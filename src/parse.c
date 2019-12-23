/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:16:24 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 23:06:54 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
** Toogle a bit of the mode variable to remember the next line will be :
** the starting node, the ending node, or both in the same time
*/

static t_bool	ft_command(const char *line, uint8_t *p_mode)
{
	if (!ft_strcmp(line, "##start"))
		*p_mode |= 0x80;
	else if (!ft_strcmp(line, "##end"))
		*p_mode |= 0x40;
	return (TRUE);
}

/*
** Parse the first line of the input and return the number of ants
*/

static int		ft_get_nb_ants(const char *line)
{
	int	i;

	if (!line)
		return (-1);
	i = 0;
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
			return (-1);
		i++;
	}
	if (i == 0)
		return (-1);
	else
		return (ft_atoi(line));
}

/*
** Execute the good parsing function accordingly to the mode variable
** mode = 0x1 if we are reading nodes
** mode = 0x2 if we are reading pipes
*/

static t_bool	ft_parse_anthill(t_anthill *anthill, const char *line,\
					uint8_t *p_mode)
{
	if (line[0] == '#')
		return (ft_command(line, p_mode));
	else
	{
		if (*p_mode & 0x1)
		{
			if (!ft_node(anthill, line, p_mode))
			{
				if (!ft_pipe(anthill, line))
					return (FALSE);
				else
					*p_mode = 0x2;
			}
		}
		else if (*p_mode & 0x2)
		{
			if (!ft_pipe(anthill, line))
				return (FALSE);
		}
	}
	return (TRUE);
}

/*
** Execute get next line and treat the line untill the first incorect line
** or EOF
*/

t_anthill		*ft_parse(void)
{
	t_anthill		*anthill;
	char			*line;
	uint8_t			mde;

	if ((!(anthill = ft_memalloc(sizeof(t_anthill)))))
		return (NULL);
	mde = 1;
	get_next_line(0, &line);
	if ((anthill->ant = ft_get_nb_ants(line)) == -1)
	{
		free(line);
		free(anthill);
		return (NULL);
	}
	ft_printf("%s\n", line);
	free(line);
	while (get_next_line(0, &line) > 0 && ft_parse_anthill(anthill, line, &mde))
	{
		ft_printf("%s\n", line);
		free(line);
	}
	free(line);
	ft_printf("\n");
	return (anthill);
}
