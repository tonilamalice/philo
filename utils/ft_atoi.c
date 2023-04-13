/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:33:14 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/13 14:49:05 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_create_out(int i, const char *str)
{
	long int	out;

	out = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		out = (out * 10) + (str[i] - 48);
		if (out > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)out);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	base;
	int	i;

	i = 0;
	base = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{	
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (sign < 0)
		return (-1);
	else if (ft_isdigit(str[i]) == 1)
	{	
		base = ft_create_out(i, str);
		return (base);
	}		
	else
		return (-1);
}


