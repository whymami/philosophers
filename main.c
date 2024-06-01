/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:28:50 by muguveli          #+#    #+#             */
/*   Updated: 2024/06/01 20:19:11 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_control(int argc, char **argv)
{
	int i, j;
	if ((argc < 5 || argc > 6) && printf("%s\n", INVALID_ARGS_ERR))
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) && printf("%s\n", INVALID_ARGS_ERR))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->philo_count = ft_atol(argv[1]);
	data->philo_live_time = ft_atol(argv[2]);
	data->philo_eat_time = ft_atol(argv[3]);
	data->philo_sleep_time = ft_atol(argv[4]);
	data->philo_dead = 0;
	if (argv[5])
		data->philo_must_eat = ft_atol(argv[5]);
	else
		data->philo_must_eat = 0;
	if (pthread_mutex_init(&data->display, NULL) && printf("%s\n",
			MUTEX_INIT_ERR))
		return (1);
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
void	display(t_philo *philo, char *msg)
{
	long long time;
	pthread_mutex_lock(&philo->data->display);
	if (philo->data->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->display);
		return ;
	}
    time = get_time() - philo->philo_start;
	printf("%lld %d %s\n", time, philo->philo_index, msg);
	pthread_mutex_unlock(&philo->data->display);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	display(philo, FORK);
	display(philo, EATING);
	if (philo->data->philo_must_eat)
		philo->philo_loop--;
	pthread_mutex_lock(&philo->philo_last_eat_mutex);
	philo->philo_last_eat = get_time();
	pthread_mutex_unlock(&philo->philo_last_eat_mutex);
	ft_usleep(philo->data->philo_eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	display(philo, SLEEPING);
	ft_usleep(philo->data->philo_sleep_time);
	display(philo, THINKING);
}

void	*philo_routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	philo->philo_last_eat = get_time();
	if (philo->data->philo_count == 1) // bunun için özel fonksiyon yaz
	{
		display(philo, FORK);
		return (NULL);
	}
	if (philo->philo_index % 2 == 0)
	{
		// usleep(philo->data->philo_eat_time * 1000);
		ft_usleep(philo->data->philo_eat_time);
		philo->philo_last_eat = get_time();
	}
	while (!philo->data->philo_dead)
	{
		if (philo->data->philo_must_eat != 0 && philo->philo_loop == 0)
			break ;
		eat(philo);
	}
	return (NULL);
}
static void stalker(t_philo *philo)
{
	while (philo->data->philo_dead != 1)
	{
		if (philo->data->philo_must_eat != 0 && philo->philo_loop == 0)
			break ;
		if ((get_time() - philo->philo_last_eat ) >= philo->data->philo_live_time)
		{
			display(philo, DEAD);
			philo->data->philo_dead = 1;
			break;
		}
	}
}

int	start_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		philo[i].philo_start = get_time();
		if (pthread_create(&philo[i].philo_thread, NULL, philo_routine,
				&philo[i]) && printf("%s\n", THREAD_CREATE_ERR))
			return (1);
	}
	stalker(philo);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(philo[i].philo_thread, NULL) && printf("%s\n",
				THREAD_JOIN_ERR))
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
	free(data);
}

int	main(int argc, char **argv)
{
	t_data data;
	t_philo *philo;
	pthread_mutex_t *forks;
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

__attribute__((destructor))
void end(void)
{
	system("leaks philo");
}