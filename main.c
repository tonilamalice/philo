/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:42:52 by ade-bast          #+#    #+#             */
/*   Updated: 2023/05/01 18:05:44 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	memset(&data, 0, sizeof(t_data));
	if (!check_args(argc, argv))
		return (1);
	if (!put_args_in_data_struct(argv, &data))
		return (1);
	data.philo = malloc(sizeof(t_philo) * data.nb_philosophers);
	if (!data.philo)
		return (1);
	while (i < data.nb_philosophers)
	{
		init_philo_struct(&data.philo[i], i + 1);
		data.philo[i].last_meal = data.begin_time;
		data.philo[i].data = &data;
		i++;
	}
	if (!thread_creation(&data))
	{
		free(data.forks);
		free(data.philo);
		return (1);
	}
	free_all(&data);
	return (0);
}
