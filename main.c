/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:42:52 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/24 20:26:37 by ade-bast         ###   ########.fr       */
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
		return;
	}
	time = time_now(philo->data);
	if (i == 0)
		printf("%ld %d has taken a fork\n", time, philo->philo_id);
	else if (i == 1)
		printf("%ld %d has taken a fork\n", time, philo->philo_id);
	else if (i == 2)
		printf("%ld %d is eating\n", time, philo->philo_id);
	else if (i == 3)
		printf("%ld %d is sleeping\n", time, philo->philo_id);
	else if (i == 4)
		printf("%ld %d is thinking\n", time, philo->philo_id);
	else if (i == 5)
		printf("%ld %d died\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->print);
}

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->someone_dead)
		printf("%ld %d died\n", time_now(philo->data), philo->philo_id);
	usleep(500);
	pthread_mutex_unlock(&philo->data->print);
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
		usleep(50);
	while (!who_dead(philo->data))
	{
		pthread_mutex_lock(&philo->data->forks[current_philo]);
		print(0, philo);
		pthread_mutex_lock(&philo->data->forks[next_philo]);
		print(1, philo);
		print(2, philo);
		my_musleep(philo->data, philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->forks[current_philo]);
		pthread_mutex_unlock(&philo->data->forks[next_philo]);
		philo->last_meal = time_now(philo->data);
		print(3, philo);
		my_musleep(philo->data, philo->data->time_to_sleep);
		print(4, philo);
	}
	return (NULL);
}

int	thread_creation(t_data *data)
{
	int	i;
	
	if (!mutex_init(data))
		return (1);
	data->threads = malloc(sizeof(data->threads) * data->number_of_philosophers + 1); 
	if (!data->threads)
		return (0);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL, philosopher, &data->philo[i]))
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

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	memset(&data, 0, sizeof(t_data));
	if (!check_args(argc, argv))
		return (1);
	put_args_in_data_struct(argv, &data);
	data.philo = malloc(sizeof * data.philo * data.number_of_philosophers);
	if (!data.philo)
		return (1);
	while (i < data.number_of_philosophers)
	{
		init_philo_struct(&data.philo[i], i + 1);
		data.philo[i].last_meal = data.begin_time;
		data.philo[i].data = &data;
		i++;
	}
	if (!thread_creation(&data))
		return (1);
	printf("Exiting from main program\n");
	return (0);
}

	// si Usleep depasse le temps imparti donc un thread principale qui verifie que le usleep n est pas plus long que le temps imparti
	// il faut que lui essaye de prendre la fourchette de gauche et que quand l autre veut prendre la fourchette de droite il n y arrive pas
