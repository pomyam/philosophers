/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:02:56 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/30 19:02:57 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_status *philo)
{
	sem_wait(philo->data->helper);
	sem_wait(philo->data->forks);
	message("has taken a left fork", philo);
	sem_wait(philo->data->forks);
	message("has taken a right fork", philo);
	sem_post(philo->data->helper);
	philo->status = EAT;
	philo->last_meal = get_time();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	message("is eating", philo);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->kol_eaten++;
}

void	live_loop(void *ph)
{
	t_status	*philo;

	if (g_flag_dead == 1)
		exit(0);
	philo = (t_status *)ph;
	eating(philo);
	philo->status = SLEEP;
	message("is sleeping", philo);
	usleep(philo->data->time_to_sleep * 1000);
	sem_wait(philo->data->doubling);
	philo->status = THINK;
	message("is thinking", philo);
	sem_post(philo->data->doubling);
}

void	*live(t_status *philo)
{
	pthread_t	thread;

	philo->last_meal = get_time();
	philo->limit = philo->last_meal + philo->data->time_to_die;
	pthread_create(&thread, NULL, (void *)&check, philo);
	pthread_detach(thread);
	while (philo->kol_eaten != philo->data->kol_eat)
	{
		live_loop(philo);
		sem_post(philo->data->doubling);
	}
	exit(0);
}

int	philosophizing(t_philo *philo)
{
	int		i;
	int		status;

	i = -1;
	while (++i < philo->num_of_philo)
	{
		philo->philo[i].pid = fork();
		if (philo->philo[i].pid < 0)
			return (1);
		else if (philo->philo[i].pid == 0)
		{
			live(&philo->philo[i]);
			exit(0);
		}
	}
	waitpid(-1, &status, 0);
	i = -1;
	while (++i < philo->num_of_philo)
		kill(philo->philo[i].pid, SIGKILL);
	free_all(philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (check_args(&philo, av, ac))
		return (1);
	if (init_philo(&philo, av))
		return (1);
	philo.philo = init_status(&philo);
	if (!philo.philo)
		return (1);
	if (philosophizing(&philo))
		return (1);
	return (0);
}
