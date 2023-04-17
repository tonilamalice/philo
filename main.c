/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:42:52 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/17 18:23:38 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	init_philo_struct(t_philo *philo, t_data *data, int i)
{
	philo->is_dead = 0;
	philo->is_sleeping = 0;
	philo->is_eating = 0;
	philo->is_thinking = 0;
	philo->took_fork_left = 0;
	philo->took_fork_right = 0;
	philo->philo_id = i;
(void) data;
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
	// if (data->philo->took_fork) ;
}


void *philosopher(void *arg)
{
	t_philo	*philo = arg;
	
	printf(" BEFORE philo %d has taken a fork\n", philo->philo_id);
	pthread_mutex_lock(&philo->data->forks[philo->philo_id]);
	printf("philo %d has taken a fork\n", philo->philo_id);
	pthread_mutex_unlock(&philo->data->forks[philo->philo_id]);
	// take_a_fork_if_available(data);
	// if (data->iter % 2 == 0)
	// 	{
	// 		usleep(30);
	// 		printf("philo %d \n", data->iter);
			
	// 	}
	// while (1)
	// {
	// 	// pthread_mutex_lock(&data->mutex);
	// 	usleep(50000);
	// 	printf("Hi from philo %d\n",data->iter);
	// 	printf("Thread %d done!\n", data->iter);
	// 	// pthread_mutex_unlock(&data->mutex);
	// }
	return NULL;
}

int	mutex_init(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	
	data->forks = malloc(sizeof(data->forks) * data->number_of_philosophers);
	if (!data->forks)
		return (0);
	data->print = malloc(sizeof(data->print) * 5);
	if (!data->print)
		return (0);
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	while (j < 5)
	{
		if (pthread_mutex_init(&data->print[j], NULL) != 0)
			return (0);
		j++;
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
		data.philo = malloc(sizeof(data.philo) * data.number_of_philosophers);
	while (k < data.number_of_philosophers)
	{
		init_philo_struct(&data.philo[k], &data, k + 1);
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
	printf("Exiting from main program\n");
	i--;
	while (i > 0)
	{
		pthread_join(data.threads[i], NULL);
		i--;
	}
	return 0;

}
// Attention philosophe ne peuvent pas communiquer entre eux 
// void	philo_creator(t_data *data, int i)

	// pthread_t th1, th2;
	// pthread_create(&th1, NULL, worker, "X");
	// pthread_create(&th2, NULL, worker, "Y");
	// sleep(1);
	// pthread_cancel(th1);
	// printf("cancelling Y\n");
	// pthread_cancel(th2);
	// printf("cancelling X\n");


	// nombre impaire commence par manger --> pair commenece par dormir
	// Tout les treads lancer au meme moment 
	// nombre pair commence par Usleep --> le temps que les autres finissent de manger 
	// si Usleep depasse le temps imparti donc un thread principale qui verifie que le usleep n est pas plus long que le temps imparti
	// il faut que lui essaye de prendre la fourchette de gauche et que quand l autre veut prendre la fourchette de droite il n y arrive pas


	// id - 1 pour les forks --> sauf sur le dernier 