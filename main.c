/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:56 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/08 18:19:56 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "Libft/libft.h"
#include "philo.h"

void print_error(void)
{
    write(1, "Error\n", 6);
    exit(1);
}

void sign_check(char **argv)
{
    int    i;
    int    j;

    i = 1;
    while (argv[i])
    {
        j = 0;
        if (argv[i][j] == '\0')
            print_error();
        while (argv[i][j])
        {
            if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != ' '
                && argv[i][j] != '+')
                print_error();
            if (argv[i][j] == '+')
                if ((argv[i][j + 1] < '0' || argv[i][j + 1] > '9') || (argv[i][j
                        - 1] >= '0' && argv[i][j - 1]))
                    print_error();
            j++;
        }
        i++;
    }
}

void arg_check(char **argv)
{
    int    i;
    int    j;

    i = 0;
    while (argv[++i])
    {
        j = -1;
        while (argv[i][++j])
            if (ft_isdigit(argv[i][j]) == 0)
                print_error();
    }
    sign_check(argv);
}

#include "stdio.h"

static void fill_data(t_philo *philo, char **argv, int argc)
{
	philo->data->nb_of_philo = ft_atoi(argv[1]);
	philo->data->t_to_die = ft_atoi(argv[2]);
	philo->data->t_to_eat = ft_atoi(argv[3]);
	philo->data->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		philo->data->nb_of_circle = ft_atoi(argv[5]);
		philo->circle_x = ft_calloc(sizeof(pthread_mutex_t), 1);
		philo->loop = ft_atoi(argv[5]);
	}
	else
		philo->data->nb_of_circle = -1;	
}

t_philo *init_struct(char **argv, int argc)
{
	int i;
	t_philo *philo;
	pthread_mutex_t *fork;
	pthread_mutex_t *write_console;

	i = -1;
	philo = ft_calloc(sizeof(t_philo), ft_atoi(argv[1]));
	fork = ft_calloc(sizeof(pthread_mutex_t), ft_atoi(argv[1]));
	write_console = ft_calloc(sizeof(pthread_mutex_t), 1);
	if (!philo || !fork || !write_console)
		print_error(); //ALLOCATION ERROR kodu yazılacak
	while (++i < ft_atoi(argv[1]))
	{
		philo[i].data = ft_calloc(sizeof(t_data), 1);
		philo[i].fork = fork;
		philo[i].data->display = write_console;
		philo[i].last_meal_x = ft_calloc(sizeof(pthread_mutex_t), 1);
		if (!philo[i].data || !philo[i].last_meal_x)
			print_error(); //ALLOCATION ERROR kodu yazılacak
		fill_data(&philo[i], argv, argc);
	}
	return (philo);
}	

long timestart(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void ft_usleep(int time)
{
	long start;
	long end;

	start = timestart();
	end = timestart();
	while (end - start < time)
	{
		usleep(100);
		end = timestart();
	}
}
void ft_write_console(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->data->display);
	printf("%ld %d %s\n", timestart() - philo->data->creation_time, philo->index, str);
	pthread_mutex_unlock(philo->data->display);
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[philo->index - 1]);
	ft_write_console(philo, FORK);
	pthread_mutex_lock(&philo->fork[(philo->index) % philo->data->nb_of_philo]);
	ft_write_console(philo, FORK);
	ft_write_console(philo, EAT);
	if (philo->data->nb_of_circle > 0)
	{
		pthread_mutex_lock(philo->circle_x);
		philo->loop--;
		pthread_mutex_unlock(philo->circle_x);
	}
	pthread_mutex_lock(philo->last_meal_x);
	philo->last_meal = timestart();
	pthread_mutex_unlock(philo->last_meal_x);
	ft_usleep(philo->data->t_to_eat);
	pthread_mutex_unlock(&philo->fork[philo->index - 1]);
	pthread_mutex_unlock(&philo->fork[(philo->index) % philo->data->nb_of_philo]);	
}

void *routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	philo->last_meal = timestart();
	if (philo->index % 2 == 0)
	{
		ft_usleep(philo->data->t_to_eat);
		philo->last_meal = timestart();
	}
	while(1)
	{
		usleep(10);
		eat(philo);
		ft_write_console(philo, SLEEP);
		ft_usleep(philo->data->t_to_sleep);
		ft_write_console(philo, THINK);
	}
	return (NULL);
}

int init_thread(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->data->nb_of_philo)
	{
		philo[i].data->creation_time = timestart();
		philo[i].index = i + 1;
		pthread_mutex_init(&philo->fork[i], NULL);
		pthread_mutex_init(philo[i].data->display, NULL);
		pthread_mutex_init(philo[i].last_meal_x, NULL);
		if (philo[i].data->nb_of_circle > 0)
			pthread_mutex_init(philo[i].circle_x, NULL);
		if (pthread_create(&philo[i].id, NULL, &routine, philo + i) != 0)
			print_error(); //THREAD ERROR kodu yazılacak
	}
	return (1);
}

int is_death(t_philo philo)
{
	pthread_mutex_lock(philo.data->display);
	pthread_mutex_lock(philo.last_meal_x);
	if ((timestart() - philo.last_meal) >= philo.data->t_to_die)
	{
		printf("%ld %d %s\n", timestart() - philo.data->creation_time, philo.index, DIE);
		return (1);
	}
	pthread_mutex_unlock(philo.last_meal_x);
	pthread_mutex_unlock(philo.data->display);
	return (0);
}

int is_circle(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->data->nb_of_philo)
	{
		pthread_mutex_lock(philo[i].circle_x);
		if (philo[i].loop > 0)
		{
			pthread_mutex_unlock(philo[i].circle_x);
			return (0);
		}
		pthread_mutex_unlock(philo[i].circle_x);
	}
	return (1);
}

int stalker(t_philo *philo)
{
	int i;

	i = -1;
	ft_usleep(15);
	while (1)
	{
		usleep(10);
		while (++i < philo->data->nb_of_philo)
			if (is_death(philo[i]))
				return (1);
		i = -1;
		if (philo->data->nb_of_circle > 0)
			if (is_circle(philo))
				return (1);
	}
}

int	main(int argc, char **argv)
{
	t_philo *philo;

	if (argc < 5 || argc > 6)
		print_error();
	arg_check(argv);
	philo = init_struct(argv, argc);
	if (!philo)
		print_error(); //ALLOCATION ERROR kodu yazılacak
	if (init_thread(philo))
		print_error(); //THREAD ERROR kodu yazılacak
	if (stalker(philo))
		print_error(); //THREAD ERROR kodu yazılacak
	
}