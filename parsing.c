/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:28:32 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/28 17:10:12 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	if (!argv)
	{
		printf("please enter arguments");
		return (0);
	}
	if (argc != 5 && argc != 6)
	{
		printf("please enter 4 or 5 arguments");
		return (0);
	}
	return (1);
}

int	put_args_in_data_struct(char **argv, t_data *data)
{
	data->someone_dead = false;
	data->nb_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->time_philosopher_must_eat = ft_atoi(argv[5]);
	if (data->nb_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("please enter only positive arguments\n");
		return (0);
	}
	if (argv[5] && data->time_philosopher_must_eat <= 0)
	{
		printf("please enter only positive arguments\n");
		return (0);
	}
	init_time(data);
	return (1);
}

void	init_philo_struct(t_philo *philo, int i)
{
	philo->is_dead = 0;
	philo->is_sleeping = 0;
	philo->is_eating = 0;
	philo->is_thinking = 0;
	philo->philo_id = i;
	philo->last_meal = 0;
}

void	free_all(t_data *data)
{
	free(data->philo);
	free(data->forks);
	free(data->threads);
}
