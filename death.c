/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:06:59 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/24 20:07:35 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_data *data)
{
	int		i;
	long	now;

	while (0 < 1)
	{
		i = 0;
		now = time_now(data);
		while (i < data->number_of_philosophers)
		{
			if (now - data->philo[i].last_meal > data->time_to_die)
				data->philo[i].is_dead = true;
			i++;
		}
		my_musleep(data, 1);
	}
}

bool	who_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (data->philo[i].is_dead)
		{
			print_dead(&data->philo[i]);
			data->someone_dead = true;
			// return (i);
			exit(1);
		}
		i++;
	}
	return (0);
}
