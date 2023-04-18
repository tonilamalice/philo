/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bast <ade-bast@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:49:31 by ade-bast          #+#    #+#             */
/*   Updated: 2023/04/18 13:06:59 by ade-bast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

struct s_data;

typedef struct s_philo
{
	int is_eating;
	int took_fork_left;
	int	took_fork_right;
	int is_sleeping;
	int is_thinking;
	int	is_dead;
	int	philo_id;
	int	*philo_table;
	struct s_data *data;
}				t_philo;

typedef struct s_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int	iter;
	t_philo *philo;
	pthread_t *threads;
	pthread_mutex_t mutex;
	pthread_mutex_t *forks;
	pthread_mutex_t *print;
}				t_data;


// Libft
char	*ft_itoa(int nbr);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
int		ft_atoi(char *str);

// Philo
void	check_args(int argc, char **argv);
void	put_args_in_data_struct(char **argv, t_data *data);

#endif