/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:28:32 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/25 13:09:28 by ade-bast         ###   ########.fr       */
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

void	init_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->begin_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int	put_args_in_data_struct(char **argv, t_data *data)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->iter = 1;
	if (argv[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("please enter only positive arguments\n");
		return (0);
	}
	if (argv[5] && data->number_of_times_each_philosopher_must_eat <= 0)
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
	philo->took_fork_left = 0;
	philo->took_fork_right = 0;
	philo->philo_id = i;
	philo->last_meal = 0;
}	

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(data->forks) * data->number_of_philosophers);
	if (!data->forks)
		return (0);
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Pthread_mutex_init() failed."));
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (printf("Pthread_mutex_init() failed."));
	return (1);
}
