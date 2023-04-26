/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:22:22 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/26 14:50:49 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(int i, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->print);
	if (philo->data->someone_dead)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	time = time_now(philo->data);
	if (i == 0)
		printf("%ld %d has taken a fork\n", time, philo->philo_id);
	else if (i == 1)
		printf("%ld %d has taken a fork\n", time, philo->philo_id);
	else if (i == 2)
	{
		printf("%ld %d is eating\n", time, philo->philo_id);
		philo->philo_meals++;		
	}
	else if (i == 3)
		printf("%ld %d is sleeping\n", time, philo->philo_id);
	else if (i == 4)
		printf("%ld %d is thinking\n", time, philo->philo_id);
	else if (i == 5)
		printf("%ld %d died\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->print);
}

void	routine(t_philo *philo, int current_philo, int next_philo)
{
	while (!who_dead(philo->data))
	{
		pthread_mutex_lock(&philo->data->forks[current_philo]);
		print(0, philo);
		if (philo->data->number_of_philosophers == 1)
		{
			pthread_mutex_unlock(&philo->data->forks[current_philo]);
			return ;
		}
		pthread_mutex_lock(&philo->data->forks[next_philo]);
		print(1, philo);
		print(2, philo);
		custom_sleep(philo->data, philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->forks[current_philo]);
		pthread_mutex_unlock(&philo->data->forks[next_philo]);
		philo->last_meal = time_now(philo->data);
		print(3, philo);
		custom_sleep(philo->data, philo->data->time_to_sleep);
		print(4, philo);
	}
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	int		current_philo;
	int		next_philo;

	philo = arg;
	current_philo = philo->philo_id - 1;
	next_philo = philo->philo_id;
	if (next_philo == philo->data->number_of_philosophers)
		next_philo = 0;
	if (philo->philo_id % 2 == 0)
		custom_sleep(philo->data, philo->data->time_to_eat / 2);
	routine(philo, current_philo, next_philo);
	return (NULL);
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

int	thread_creation(t_data *data)
{
	int	i;

	if (!mutex_init(data))
		return (1);
	data->threads = malloc(sizeof(data->threads)
			* data->number_of_philosophers + 1);
	if (!data->threads)
		return (0);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL,
				philosopher, &data->philo[i]))
			return (0);
		i++;
		data->iter++;
	}
	i--;
	check_death(data);
	while (i > 0)
	{
		pthread_join(data->threads[i], NULL);
		i--;
	}
	return (1);
}
