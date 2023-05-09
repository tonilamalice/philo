/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:06:59 by ade-bast          #+#    #+#             */
/*   Updated: 2023/05/01 11:45:37 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->someone_dead)
		printf("%ld %d died\n", time_now(philo->data), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print);
}

static int	all_eaten(t_data *data)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (i < data->nb_philosophers)
	{
		if (data->time_philosopher_must_eat)
		{
			if (data->philo[i].philo_meals >= data->time_philosopher_must_eat)
				flag += 1;
		}
			i++;
	}
	if (flag == data->nb_philosophers)
	{
		data->someone_dead = true;
		return (1);
	}
	return (0);
}

bool	who_dead(t_data *data)
{
	int		i;
	long	now;

	while (1)
	{
		i = 0;
		now = time_now(data);
		while (i < data->nb_philosophers)
		{
			if ((now - data->philo[i].last_meal) > data->time_to_die)
			{
				print_dead(&data->philo[i]);
				data->someone_dead = true;
				return (i);
			}
			i++;
		}
		if (all_eaten(data))
			return (1);
	}
	return (0);
}
