/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:02:17 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/30 19:02:18 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(char *str, t_status *philo)
{
	pthread_mutex_lock(&philo->all->message);
	if (philo->all->kol_eat != -1)
		printf("%ld %d %s %d times\n", get_time() - philo->all->start,
			philo->number, str, philo->have_eaten);
	else
		printf("%ld %d %s\n", get_time() - philo->all->start,
			   philo->number, str);
	pthread_mutex_unlock(&philo->all->message);
}

void	*check_eat(void *ph)
{
	t_philo		*phil;
	int			i;

	phil = (t_philo *)ph;
	while (1)
	{
		i = 0;
		while (i < phil->num_of_philo)
		{
			if (phil->ph[i].have_eaten < phil->kol_eat)
				break ;
			i++;
		}
		if (i == phil->num_of_philo)
			break ;
		usleep(1000);
	}
	pthread_mutex_lock(&phil->message);
	printf("All philos are feed\n");
	pthread_mutex_unlock(&phil->dead_philo);
	return (NULL);
}

void	*checker(void *ph)
{
	t_status		*phil;

	phil = (t_status *)ph;
	while (1)
	{
		pthread_mutex_lock(&phil->check);
		if (get_time() > phil->time_to_death)
		{
			pthread_mutex_lock(&phil->all->message);
			printf("%ld %d died\n", get_time() - \
				phil->all->start, phil->number);
			pthread_mutex_unlock(&phil->check);
			pthread_mutex_unlock(&phil->all->dead_philo);
			return (NULL);
		}
		pthread_mutex_unlock(&phil->check);
		usleep(1000);
	}
}

int	check_args(t_philo *philo, char **av, int ac)
{
	philo->num_of_philo = -1;
	philo->time_to_die = -1;
	philo->time_to_eat = -1;
	philo->time_to_sleep = -1;
	philo->kol_eat = -1;
	if (ac > 6 || ac < 5)
		return (ft_error("Error: wrong number of arguments!\n"));
	philo->num_of_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (philo->num_of_philo < 1 || philo->time_to_die < 60
		|| philo->time_to_eat < 60 || philo->time_to_sleep < 60
		|| philo->num_of_philo > 200)
		return (ft_error("Error: strange arguments!\n"));
	if (ac == 6)
	{
		philo->kol_eat = ft_atoi(av[5]);
		if (philo->kol_eat < 1)
			return (ft_error("Error: incorrect fifth argument!\n"));
	}
	return (0);
}
