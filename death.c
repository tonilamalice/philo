/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:06:59 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/26 16:56:14 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->someone_dead)
		printf("%ld %d died\n", time_now(philo->data), philo->philo_id);
	// usleep(500);
	// pthread_mutex_unlock(&philo->data->print);
}

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
			{
				data->philo[i].is_dead = true;
				data->someone_dead = true;
			}
			i++;
		}
		custom_sleep(data, 1);
	}
}

static int	all_eaten(t_data *data)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (data->philo[i].philo_meals >= data->number_of_times_each_philosopher_must_eat)
			flag += 1;
		i++;
	}
	if (flag == data->number_of_philosophers)
	{
		data->someone_dead = true;
		return (1);		
	}
	return (0);
}

bool	who_dead(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			if (data->philo[i].is_dead)
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
