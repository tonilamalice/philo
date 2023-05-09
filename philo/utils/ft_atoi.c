/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:33:14 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/25 11:42:52 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	base;
	int	i;

	i = 0;
	base = 0;
	while (ft_isdigit(str[i]))
	{
		base = base * 10 + str[i] - '0';
		if (base < 0)
			return (-1);
		i++;
	}
	if (str[i] || !i)
		return (-1);
	return (base);
}
