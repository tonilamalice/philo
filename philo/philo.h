/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:49:31 by ade-bast          #+#    #+#             */
/*   Updated: 2023/05/09 13:27:11 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdatomic.h>

struct	s_data;

typedef struct s_philo
{
	atomic_long		last_meal;
	int				philo_id;
	struct s_data	*data;
	atomic_int		philo_meals;
}				t_philo;

typedef struct s_data
{
	atomic_bool		someone_dead;
	int				nb_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	atomic_int		time_philosopher_must_eat;
	t_philo			*philo;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	long			begin_time;
}				t_data;

// Libft
int		ft_atoi(char *str);

// Philo
int		check_args(int argc, char **argv);
int		put_args_in_data_struct(char **argv, t_data *data);
void	init_philo_struct(t_philo *philo, int i);
int		mutex_init(t_data *data);
void	custom_sleep(t_data *data, long time);
long	time_now(t_data *data);
bool	who_dead(t_data *data);
void	print_dead(t_philo *philo);
void	print(int i, t_philo *philo);
void	routine(t_philo *philo, int current_philo, int next_philo);
void	*philosopher(void *arg);
int		thread_creation(t_data *data);
void	init_time(t_data *data);
void	free_all(t_data *data);
int		free_custom(int i, t_data *data);
void	init_failed(t_data *data, int i);
#endif