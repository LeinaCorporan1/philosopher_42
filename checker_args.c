/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:06:15 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/21 18:53:03 by lcorpora         ###   ########.fr       */
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

int	check_args(char **av, int ac)
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
				ft_error("Invalid arguments\n");
			y++;
		}
		i++;
	}
	return (rtn);
}
