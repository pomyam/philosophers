/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:02:21 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/30 19:02:22 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

static int	ft_spaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\f'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == 32)
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	nb;

	i = ft_spaces(str);
	sign = 1;
	nb = 0;
	while (str[i] == 43 || str[i] == 45)
	{
		if (str[i + 1] == 43 || str[i + 1] == 45)
			return (0);
		if (str[i] == 45)
			sign = sign * -1;
		i++;
	}
	nb = str[i] - '0';
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (str[i + 1] >= 48 && str[i + 1] <= 57)
			nb = nb * 10 + (str[i + 1] - '0');
		else
			return (nb * sign);
		i++;
	}
	return (0);
}

time_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (time_t)1000) + time.tv_usec / 1000);
}
