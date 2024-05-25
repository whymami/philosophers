/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:53:48 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/25 18:04:47 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	philo->last_eat = get_time();
	if (philo->philo_idx % 2 == 0)
	{
		ft_usleep(philo->data->eat_time);
		philo->last_eat = get_time();
	}
	while (1)
	{
		usleep(10);
		eat(philo);
		display(philo, SLEEPING);
		ft_usleep(philo->data->sleep_time);
		display(philo, THINKING);
	}
}

pthread_mutex_t	*init_mutex(char **argv)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * ft_atol(argv[1]));
	if (!forks && printf("%s\n", MALLOC_ERR))
		return (NULL);
	i = -1;
	while (++i < ft_atol(argv[1]))
		if (pthread_mutex_init(&forks[i], NULL) && printf("%s\n",
				MUTEX_INIT_ERR))
			return (NULL);
	return (forks);
}

static void	fill_data(t_philo *philo, char **argv, int argc)
{
	philo->data->philo_count = ft_atol(argv[1]);
	philo->data->live_time = ft_atol(argv[2]);
	philo->data->eat_time = ft_atol(argv[3]);
	philo->data->sleep_time = ft_atol(argv[4]);
	if (argc == 6)
	{
		philo->data->must_eat = ft_atol(argv[5]);
		philo->loop_count_mutex = malloc(sizeof(pthread_mutex_t));
		if (!philo->loop_count_mutex && printf("%s\n", MALLOC_ERR))
			return ;
		philo->loop_count = ft_atol(argv[5]);
	}
	else
		philo->data->must_eat = -1;
}

t_philo	*init_philo(char **argv, int argc, pthread_mutex_t *forks)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*display;

	i = -1;
	philo = malloc(sizeof(t_philo) * ft_atol(argv[1]));
	display = malloc(sizeof(pthread_mutex_t));
	if (!(philo || !display) && printf("%s\n", MALLOC_ERR))
		return (NULL);
	while (++i < ft_atol(argv[1]))
	{
		philo[i].data = malloc(sizeof(t_data));
		philo[i].last_eat_mutex = malloc(sizeof(pthread_mutex_t));
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % ft_atol(argv[1])];
		if (!(philo[i].data || philo[i].last_eat_mutex) && printf("%s\n",
				MALLOC_ERR))
			return (NULL);
		philo[i].data->display = display;
		fill_data(&philo[i], argv, argc);
	}
	return (philo);
}

int	init_thread(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->philo_count)
	{
		philo[i].data->start_time = get_time();
		philo[i].philo_idx = i + 1;
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_mutex_init(philo[i].right_fork, NULL);
		pthread_mutex_init(philo[i].data->display, NULL);
		pthread_mutex_init(philo[i].last_eat_mutex, NULL);
		if (philo[i].data->must_eat > 0)
			pthread_mutex_init(philo[i].loop_count_mutex, NULL);
		if (pthread_create(&philo[i].thread_id, NULL, &routine, philo + i))
			exit(1);
	}
	return (1);
}
