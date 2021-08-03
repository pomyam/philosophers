/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:02:48 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/30 19:02:49 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_status	*init_status(t_philo *data)
{
	t_status	*philos;
	int			i;

	i = 0;
	philos = (t_status *)malloc(sizeof(t_status) * data->num_of_philo);
	if (!philos)
		return (NULL);
	while (i < data->num_of_philo)
	{
		philos[i].limit = 0;
		philos[i].status = THINK;
		philos[i].number = i + 1;
		philos[i].data = data;
		philos[i].kol_eaten = 0;
		i++;
	}
	return (philos);
}

int	init_philo(t_philo *philo, char **av)
{
	philo->start = get_time();
	philo->flag_dead = 0;
	sem_unlink("forks");
	philo->forks = sem_open("forks", O_CREAT | O_EXCL, \
	0644, philo->num_of_philo);
	sem_unlink("print");
	philo->print = sem_open("write", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("helper");
	philo->helper = sem_open("helper", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("doubling");
	philo->helper = sem_open("doubling", O_CREAT | O_EXCL, \
	0777, philo->num_of_philo);
	sem_unlink("dead");
	g_dead = sem_open("dead", O_CREAT | O_EXCL, 0777, 1);
	return (0);
}
