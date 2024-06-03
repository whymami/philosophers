/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:34:17 by muguveli          #+#    #+#             */
/*   Updated: 2024/06/02 19:50:40 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv)
{
	data->philo_count = ft_atol(argv[1]);
	if (data->philo_count < 1 && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	data->philo_live_time = ft_atol(argv[2]);
	data->philo_eat_time = ft_atol(argv[3]);
	data->philo_sleep_time = ft_atol(argv[4]);
	data->philo_dead = 0;
	if (argv[5])
		data->philo_must_eat = ft_atol(argv[5]);
	else
		data->philo_must_eat = -1;
	if (pthread_mutex_init(&data->display, NULL) && printf("%s\n",
			MUTEX_INIT_ERR))
		return (1);
	return (0);
}

int	arg_control(int argc, char **argv)
{
	int	i;
	int	j;

	if ((argc < 5 || argc > 6) && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]) && printf("%s\n", INVALID_ARGS_ERR))
				return (1);
	}
	return (0);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!forks && printf("%s\n", MALLOC_ERR))
		return (NULL);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_mutex_init(&forks[i], NULL) && printf("%s\n",
				MUTEX_INIT_ERR))
			return (NULL);
	return (forks);
}

t_philo	*init_philo(t_data *data, pthread_mutex_t *forks)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!philo && printf("%s\n", MALLOC_ERR))
		return (NULL);
	i = -1;
	while (++i < data->philo_count)
	{
		philo[i].philo_index = i + 1;
		if (data->philo_must_eat)
			philo[i].philo_loop = data->philo_must_eat;
		else
			philo[i].philo_loop = 0;
		philo[i].philo_last_eat = get_time();
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % data->philo_count];
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].philo_last_eat_mutex, NULL)
			&& printf("%s\n", MUTEX_INIT_ERR))
			return (NULL);
	}
	return (philo);
}
