/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:02:31 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/30 19:02:32 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_philo);
	pthread_mutex_destroy(philo->forks);
	free(philo->forks);
	free(philo->ph);
	exit(0);
}

void	live_loop(void *ph)
{
	t_status	*phil;

	phil = (t_status *)ph;
	if (phil->number % 2 == 0)
		usleep(phil->all->time_to_eat);
	pthread_mutex_lock(&phil->all->forks[phil->left_fork]);
	message("take a left fork", ph);
	pthread_mutex_lock(&phil->all->forks[phil->right_fork]);
	message("take a right fork", ph);
	message("is eating", ph);
	usleep(phil->all->time_to_eat * 1000);
	pthread_mutex_unlock(&phil->all->forks[phil->right_fork]);
	message("left a right fork", ph);
	pthread_mutex_unlock(&phil->all->forks[phil->left_fork]);
	message("left a left fork", ph);
	phil->have_eaten += 1;
	phil->time_to_death = get_time() + phil->all->time_to_die;
	message("is sleeping", ph);
	usleep(phil->all->time_to_sleep * 1000);
	message("is thinking", ph);
}

void	*live(void *ph)
{
	t_status	*p;
	pthread_t	tid;

	p = (t_status *)ph;
	p->last_meal = get_time();
	p->time_to_death = p->last_meal + p->all->time_to_die;
	if (pthread_create(&tid, NULL, &checker, ph) != 0)
		return ((void *)1);
	if (pthread_detach(tid) != 0)
		return ((void *)1);
	while (1)
	{
		live_loop(p);
	}
	return (NULL);
}

int	philosophizing(t_philo *philo)
{
	int			i;
	pthread_t	thread;

	i = 0;
	philo->start = get_time();
	if (philo->kol_eat != -1)
	{
		if (pthread_create(&thread, NULL, &check_eat, philo) != 0)
			return (1);
		if (pthread_detach(thread) != 0)
			return (1);
	}
	while (i < philo->num_of_philo)
	{
		philo->ph[i].time_to_death = get_time() + philo->ph[i].all->time_to_die;
		if (pthread_create(&philo->ph[i].thread, \
			NULL, &live, (void *)(&philo->ph[i])) != 0)
			return (1);
		if (pthread_detach(philo->ph[i].thread) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (check_args(&philo, argv, argc))
		return (1);
	if (init_philos(&philo))
		return (1);
	if (init_forks(&philo))
		return (1);
	if (philosophizing(&philo))
		return (1);
	free_all(&philo);
	return (0);
}
