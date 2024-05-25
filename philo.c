/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:59:54 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/25 18:09:41 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	display(philo, FORK);
	display(philo, EATING);
	if (philo->data->must_eat > 0)
	{
		pthread_mutex_lock(philo->loop_count_mutex);
		philo->loop_count--;
		pthread_mutex_unlock(philo->loop_count_mutex);
	}
	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->last_eat_mutex);
	ft_usleep(philo->data->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	is_dead(t_philo philo)
{
	pthread_mutex_lock(philo.last_eat_mutex);
	pthread_mutex_lock(philo.data->display);
	if ((get_time() - philo.last_eat) >= philo.data->live_time)
	{
		printf("%lld %d %s\n", get_time() - philo.data->start_time,
			philo.philo_idx, DEAD);
		return (1);
	}
	pthread_mutex_unlock(philo.last_eat_mutex);
	pthread_mutex_unlock(philo.data->display);
	return (0);
}

static int	is_okey(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->philo_count)
	{
		pthread_mutex_lock(philo[i].loop_count_mutex);
		if (philo[i].loop_count > 0)
		{
			pthread_mutex_unlock(philo[i].loop_count_mutex);
			return (0);
		}
		pthread_mutex_unlock(philo[i].loop_count_mutex);
	}
	return (1);
}

int	stalker(t_philo *philo)
{
	int	i;

	ft_usleep(15);
	while (1)
	{
		usleep(10);
		i = -1;
		while (++i < philo->data->philo_count)
			if (is_dead(philo[i]))
				return (1);
		if (philo->data->must_eat > 0)
			if (is_okey(philo))
				return (1);
	}
}
