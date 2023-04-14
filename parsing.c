/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:28:32 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/14 12:48:13 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	check_args(int argc, char **argv)
{
	if (!argv)
	{
		printf("please enter arguments");
		exit(EXIT_FAILURE); //! Attention exit not allowed
	}

	if (argc != 5 && argc != 6)
	{
		printf("please enter 4 or 5 arguments");
		exit(EXIT_FAILURE);
	}
}

void	put_args_in_data_struct(char **argv, t_data *data)
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
		printf("%d %d %d %d %dplease enter only positive arguments\n",data->time_to_die, data->number_of_philosophers, data->number_of_times_each_philosopher_must_eat, data->time_to_eat, data->time_to_sleep);
		exit(EXIT_FAILURE);
	}
	if (argv[5] && data->number_of_times_each_philosopher_must_eat <= 0)
	{
		printf("%d %d %d %d %dplease enter only positive arguments\n",data->time_to_die, data->number_of_philosophers, data->number_of_times_each_philosopher_must_eat, data->time_to_eat, data->time_to_sleep);
		exit(EXIT_FAILURE);
	}
}

