/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:25:24 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/22 12:31:51 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_musleep(t_data *data, long time)
{
	long	now;
	long	start;
	int		who;

	start = time_now(data);
	while (!who_dead(data))
	{
		now = time_now(data);
		if (now - start >= time)
			break ;
		usleep(100);
	}
	who = who_dead(data);
	if (who)
	{
		print_dead(who, &data->philo[who]);
		exit(1);
	}
}

long	time_now(t_data *data)
{
	long			res;
	struct timeval	time;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res - data->begin_time);
}