/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:02:41 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/30 19:02:42 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	message(char *str, t_status *philo)
{
	sem_wait(philo->data->print);
	if (philo->data->kol_eat != -1)
	{
		printf("%d\t", get_time() - philo->data->start);
		printf("%d ", philo->number);
		printf("%s ", str);
		printf("%d times\n", philo->data->kol_eat - philo->kol_eaten);
	}
	else
	{
		printf("%d\t", get_time() - philo->data->start);
		printf("%d ", philo->number);
		printf("%s\n", str);
	}
	sem_post(philo->data->print);
}

void	free_all(t_philo *data)
{
	sem_wait(data->print);
	sem_wait(data->helper);
	sem_wait(data->doubling);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("die");
	sem_unlink("helper");
	sem_unlink("dead");
	free(data->philo);
}

void	*check(t_status *philo)
{
	while (1)
	{
		if (philo->kol_eaten == philo->data->kol_eat)
		{
			free_all(philo->data);
			printf("All philo are feed!\n");
			exit(0);
		}
		if (philo->status != EAT && get_time() > philo->limit)
		{
			philo->status = DIE;
			sem_wait(g_dead);
			g_flag_dead = 1;
			message("is dead", philo);
			free_all(philo->data);
			exit(0);
		}
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
		return (ft_error("Error: wrong number of arguments!"));
	philo->num_of_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (philo->num_of_philo < 1 || philo->time_to_die < 60
		|| philo->time_to_eat < 60 || philo->time_to_sleep < 60
		|| philo->num_of_philo > 200)
		return (ft_error("Error: strange arguments!"));
	if (ac == 6)
	{
		philo->kol_eat = ft_atoi(av[5]);
		if (philo->kol_eat < 1)
			return (ft_error("Error: incorrect fifth argument!"));
	}
	return (0);
}
