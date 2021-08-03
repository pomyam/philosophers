/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:03:00 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/30 19:03:01 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

# define EAT			0
# define THINK			1
# define SLEEP			2
# define DIE			-1

sem_t		*g_dead;
int			g_flag_dead;

typedef struct s_philo
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				kol_eat;
	int				start;
	int				flag_dead;
	struct s_status	*philo;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*helper;
	sem_t			*doubling;
}					t_philo;

typedef struct s_status
{
	int				number;
	int				status;
	int				limit;
	int				last_meal;
	int				kol_eaten;
	pid_t			pid;
	t_philo			*data;
}					t_status;

int			init_philo(t_philo *philo, char **av);
t_status	*init_status(t_philo *data);
int			ft_error(char *str);
void		*check(t_status *philo);
int			check_args(t_philo *philo, char **av, int ac);
int			ft_strlen(char *str);
int			ft_atoi(const char *str);
int			get_time(void);
void		message(char *str, t_status *philo);
void		free_all(t_philo *data);
#endif
