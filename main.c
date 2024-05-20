/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:08:51 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/20 20:34:50 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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

int	init_data(t_data *data, char **argv)
{
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->is_dead = 0;
	if (argv[5])
		data->num_of_must_eat = ft_atoi(argv[5]);
	else
		data->num_of_must_eat = -1;
	if (pthread_mutex_init(&data->display_mutex, NULL) && printf("%s\n",
			MUTEX_INIT_ERR))
		return (1);
	return (0);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_of_philo);
	if (!forks && printf("%s\n", MALLOC_ERR))
		return (NULL);
	i = -1;
	while (++i < data->num_of_philo)
		if (pthread_mutex_init(&forks[i], NULL) && printf("%s\n",
				MUTEX_INIT_ERR))
			return (NULL);
	return (forks);
}

t_philo	*init_philo(t_data *data, pthread_mutex_t *fork_arr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (!philo && printf("%s\n", MALLOC_ERR))
		return (NULL);
	i = -1;
	while (++i < data->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].nbr_of_meals = 0;
		philo[i].left_fork = &fork_arr[i];
		philo[i].right_fork = &fork_arr[(i + 1) % data->num_of_philo];
		philo[i].last_meal_time = get_time();
		philo[i].data = data;
	}
	return (philo);
}

void	display_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->data->display_mutex);
	time = get_time() - philo->start_time;
	printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->display_mutex);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		display_status(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		display_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		display_status(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		display_status(philo, FORK);
	}
	display_status(philo, EATING);
	philo->nbr_of_meals++;
	philo->last_meal_time = get_time();
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	display_status(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
	display_status(philo, THINKING);
}

void	*live(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->is_dead)
	{
		if (philo->data->num_of_must_eat != -1
			&& philo->nbr_of_meals >= philo->data->num_of_must_eat)
			break ;
		take_forks(philo);
		if (get_time() - philo->last_meal_time >= philo->data->time_to_die)
		{
			display_status(philo, DEAD);
			philo->data->is_dead = 1;
			break ;
		}
	}
	return (NULL);
}

int	start_simulation(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		philo[i].start_time = get_time();
		if (pthread_create(&philo[i].thread_id, NULL, live, &philo[i])
			&& printf("%s\n", THREAD_CREATE_ERR))
			return (1);
	}
	i = -1;
	while (++i < data->num_of_philo)
		if (pthread_join(philo[i].thread_id, NULL) && printf("%s\n",
				THREAD_JOIN_ERR))
			return (1);
	return (0);
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
	if (!start_simulation(philo, &data))
		return (1);
}
