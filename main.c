/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:42:52 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/14 15:17:48 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_struct(t_philo *philo)
{
	philo->is_dead = 0;
	philo->is_sleeping = 0;
	philo->is_eating = 0;
	philo->is_thinking = 0;
	philo->took_fork = 0;
	philo->philo_id = 1;
}

void	take_a_fork_if_available(t_data *data)
{
	if (data->philo->philo_id % 2 != 0)
	{
		data->philo->took_fork++;
		printf("philo %d has taken a fork\n", data->philo->philo_id);
	}
	// if (data->philo->took_fork) ;
	
}

void *philosopher(void *arg)
{
	t_data *data = arg;
	pthread_mutex_lock(&data->mutex);
	usleep(50000);
	printf("Hi from philo %d\n",data->iter);
	// if (data->philo->philo_id % 2 == 0)
	take_a_fork_if_available(data);
	printf("Thread %d done!\n", data->iter);
	pthread_mutex_unlock(&data->mutex);
	return NULL;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo philo;
	int		i;
	pthread_t *threads;
	// pthread_mutex_t mutex;
	
	check_args(argc, argv);
	put_args_in_data_struct(argv, &data);
	init_philo_struct(&philo);
	data.philo = &philo;
	// data.mutex = mutex;
	threads = malloc(sizeof(threads) * data.number_of_philosophers + 1); //! to be protected
	if (pthread_mutex_init(&data.mutex, NULL) != 0)
		return (0);
	i = 1;
	while (i < data.number_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL, philosopher, &data))
			return (0);
		sleep(1);
		i++;
		data.iter++;
		philo.philo_id = data.iter;
	}
	printf("Exiting from main program\n");
	i--;
	while (i > 0)
	{
		pthread_join(threads[i], NULL);
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