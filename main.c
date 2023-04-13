/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:42:52 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/13 18:30:57 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher(t_data *test)
{

usleep(50000);
printf("Hi from thread name = %d\n",test->iter);
printf("Thread %d done!\n", test->iter);
return NULL;
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	pthread_t *threads;
	
	data.iter = 0;
	threads = malloc(sizeof(threads) * data.number_of_philosophers + 1);
	i = 1;
	check_args(argc, argv);
	put_args_in_data_struct(argv, &data);
	while (i < data.number_of_philosophers)
	{
		pthread_create(&threads[i], NULL, (void *)philosopher, &data);
		sleep(1);
		printf("%d",i);
		i++;
		data.iter++;
	}
	printf("Exiting from main program\n");
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