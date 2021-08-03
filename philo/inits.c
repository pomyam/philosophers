/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:02:25 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/30 19:02:26 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo *philo)
{
	int	i;

	i = -1;
	philo->ph = (t_status *)malloc(sizeof(t_status) * philo->num_of_philo);
	if (philo->ph == NULL)
		return (1);
	while (++i < philo->num_of_philo)
	{
		philo->ph[i].last_meal = 0;
		philo->ph[i].have_eaten = 0;
		philo->ph[i].number = i + 1;
		philo->ph[i].left_fork = i;
		philo->ph[i].right_fork = (i + 1) % philo->num_of_philo;
		philo->ph[i].all = philo;
	}
	return (0);
}

int	init_forks(t_philo *philo)
{
	int	i;

	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	if (philo->forks == NULL)
		return (1);
	i = -1;
	while (++i < philo->num_of_philo)
		pthread_mutex_init(&philo->forks[i], NULL);
	pthread_mutex_init(&philo->message, NULL);
	pthread_mutex_init(&philo->dead_philo, NULL);
	pthread_mutex_lock(&philo->dead_philo);
	return (0);
}
