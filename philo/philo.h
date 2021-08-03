/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:02:34 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/30 19:02:35 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <signal.h>

struct	s_status;

typedef struct s_philo
{
	int				num_of_philo;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_to_die;
	int				kol_eat;
	time_t			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_philo;
	pthread_mutex_t	message;
	struct s_status	*ph;
}					t_philo;

typedef struct s_status
{
	int				number;
	pthread_t		thread;
	pthread_mutex_t	check;
	int				have_eaten;
	int				left_fork;
	int				right_fork;
	time_t			last_meal;
	time_t			time_to_death;
	t_philo			*all;
}				t_status;

int		ft_atoi(const char *str);
int		check_args(t_philo *philo, char **av, int ac);
time_t	get_time(void);
void	*checker(void *ph);
void	*check_eat(void *ph);
int		init_forks(t_philo *philo);
int		init_philos(t_philo *philo);
void	message(char *str, t_status *phil);
int		ft_error(char *str);
void	free_all(t_philo *philo);

#endif