/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:28:50 by muguveli          #+#    #+#             */
/*   Updated: 2024/06/02 19:49:56 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int control_data(t_data *data)
{
	if (data->philo_count < 1 && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	if (data->philo_live_time < 60 && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	if (data->philo_eat_time < 60 && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	if (data->philo_sleep_time < 60 && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	if (data->philo_must_eat == 0)
		return (1);
	return (0);
}

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
	if (control_data(&data))
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
