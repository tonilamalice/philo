/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:49:31 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/22 12:45:10 by ade-bast         ###   ########.fr       */
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

struct	s_data;

typedef struct s_philo
{
	bool	is_eating;
	bool	took_fork_left;
	bool	took_fork_right;
	bool	is_sleeping;
	bool	is_thinking;
	bool	is_dead;
	long	last_meal;
	int		philo_id;
	int		*philo_table;
	struct	s_data *data;
}				t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				iter;
	t_philo			*philo;
	pthread_t		*threads;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	long			begin_time;
}				t_data;

// Libft
char	*ft_itoa(int nbr);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
int		ft_atoi(char *str);

// Philo
int		check_args(int argc, char **argv);
void	put_args_in_data_struct(char **argv, t_data *data);
void	init_philo_struct(t_philo *philo, int i);
int		mutex_init(t_data *data);
void	my_musleep(t_data *data, long time);
long	time_now(t_data *data);
bool	who_dead(t_data *data);
void	print_dead(int i, t_philo *philo);
#endif