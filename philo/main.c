/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:28:50 by muguveli          #+#    #+#             */
/*   Updated: 2024/06/01 21:07:16 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_data *data, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	if (data)
		pthread_mutex_destroy(&data->display);
	if (forks)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			pthread_mutex_destroy(&forks[i]);
			pthread_mutex_destroy(&philos[i].philo_last_eat_mutex);
			philos[i].left_fork = NULL;
			philos[i].right_fork = NULL;
		}
		free(&philos->philo_last_eat_mutex);
	}
	if (data)
		free(data);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (arg_control(argc, argv) || init_data(&data, argv))
		return (1);
	forks = init_forks(&data);
	if (!forks)
		return (1);
	philo = init_philo(&data, forks);
	if (!philo)
		return (1);
	if (start_simulation(&data, philo))
		destroy(&data, forks, philo);
	free(forks);
	free(philo);
}
