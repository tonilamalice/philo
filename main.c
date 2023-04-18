/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:42:52 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/18 15:33:56 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

void	init_philo_struct(t_philo *philo, int i)
{
	philo->is_dead = 0;
	philo->is_sleeping = 0;
	philo->is_eating = 0;
	philo->is_thinking = 0;
	philo->took_fork_left = 0;
	philo->took_fork_right = 0;
	philo->philo_id = i;
}	

void	take_a_fork_if_available(t_data *data)
{
	if (data->philo->philo_id == 1)
		{
			data->philo->took_fork_left = 1;
			data->philo->took_fork_right = 1;
		}
	
	if (data->philo->philo_id % 2 != 0)
	{
		data->philo->took_fork_left++;
		printf("philo %d has taken a fork\n", data->philo->philo_id);
	}

}

long	time_now(void)
{
	long			res;
	struct timeval	time;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

void	print(int	i, t_philo *philo)
{
	if (i == 0)
	{
		printf("philo %d fork has been taken\n", philo->philo_id);
		pthread_mutex_lock(&philo->data->print[0]);
	}
	if (i == 1)
	{
			printf("philo %d fork 2 has been taken\n", philo->philo_id);
			pthread_mutex_lock(&philo->data->print[1]);
	}
	if (i == 2)
	{
			printf("philo %d is sleeping\n", philo->philo_id);
			pthread_mutex_lock(&philo->data->print[2]);
	}
}

void *philosopher(void *arg)
{
	t_philo	*philo = arg;
	
	int	i;
	i = 0;
	// usleep(philo->data->time_to_eat);
	usleep(500);
	while (0 < 10000)
	{
		
	if (philo->philo_id % 2 == 0)
	{
		usleep(10000);
	}
	pthread_mutex_lock(&philo->data->forks[philo->philo_id]);
	// pthread_mutex_lock(&philo->data->print[0]);
	print(0, philo);
	pthread_mutex_lock(&philo->data->forks[philo->philo_id + 1]);
	
	print(1, philo);
	print(2, philo);
	// printf("philo %d is eating\n", philo->philo_id);
	// printf("philo %d is sleeping\n", philo->philo_id);
	usleep(5000);
	pthread_mutex_unlock(&philo->data->forks[philo->philo_id]);
	i++;
	}

	// take_a_fork_if_available(data);
	// if (data->iter % 2 == 0)
	// 	{
	// 		usleep(30);
	// 		printf("philo %d \n", data->iter);
			
	// 	}
	return NULL;
}

int	mutex_init(t_data *data)
{
	int	i;
	
	i = 0;
	data->forks = malloc(sizeof(data->forks) * data->number_of_philosophers);
	if (!data->forks)
		return (0);
	data->print = malloc(sizeof(data->print) * 5);
	if (!data->print)
		return (0);
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Pthread_mutex_init() failed."));
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (pthread_mutex_init(&data->print[i], NULL) != 0)
			return (printf("Pthread_mutex_init() failed."));
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		k;
	
	k = 0;
	memset(&data, 0, sizeof(t_data));
	check_args(argc, argv);
	put_args_in_data_struct(argv, &data);
	data.philo = malloc(sizeof *data.philo * data.number_of_philosophers);
	if (!data.philo)
		return (1);
	while (k < data.number_of_philosophers)
	{
		init_philo_struct(&data.philo[k], k + 1);
		data.philo[k].data = &data;
		k++;
	}
	if (!mutex_init(&data))
		return (1);
	data.threads = malloc(sizeof(data.threads) * data.number_of_philosophers + 1); 
	if (!data.threads)
		return (1);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		if (pthread_create(&data.threads[i], NULL, philosopher, &data.philo[i]))
			return (0);
		sleep(1);
		i++;
		data.iter++;
	}
	i--;
	while (i > 0)
	{
		pthread_join(data.threads[i], NULL);
		i--;
	}
	printf("Exiting from main program\n");
	return 0;

}
// Attention philosophe ne peuvent pas communiquer entre eux 
// void	philo_creator(t_data *data, int i)

	// nombre impaire commence par manger --> pair commenece par dormir
	// Tout les treads lancer au meme moment 
	// nombre pair commence par Usleep --> le temps que les autres finissent de manger 
	// si Usleep depasse le temps imparti donc un thread principale qui verifie que le usleep n est pas plus long que le temps imparti
	// il faut que lui essaye de prendre la fourchette de gauche et que quand l autre veut prendre la fourchette de droite il n y arrive pas


	// id - 1 pour les forks --> sauf sur le dernier 