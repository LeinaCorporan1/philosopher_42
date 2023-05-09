/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 03:57:33 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/26 13:17:00 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *c)
{
	size_t	count;

	count = 0;
	while (*c)
	{	
		count++;
		c++;
	}
	return (count);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	check_args(char **av)
{
	int	i;
	int	y;
	int	rtn;

	i = 1;
	rtn = 0;
	while (av[i])
	{
		if (ft_strlen(av[i]) > 10 || ft_atoi(av[i]) < 0
			|| ft_atoi(av[i]) > INT_MAX)
			rtn = 1;
		y = 0;
		while (av[i][y])
		{
			if (!ft_isdigit(av[i][y]))
				rtn = 1;
			if (rtn == 1)
				return (ft_error("Invalid arguments\n"), 1);
			y++;
		}
		i++;
	}
	return (rtn);
}
