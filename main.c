/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:56 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/07 19:57:49 by muguveli         ###   ########.fr       */
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

static int init_mutex(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->philo_count)
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (1);
	return (0);
}

void init_philo(t_rules *rules, char **argv)
{
	rules->philo_count = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->must_eat_count = ft_atoi(argv[5]);
	else
		rules->must_eat_count = -1;
	if (rules->philo_count > 250)
		print_error();
	if (init_mutex(rules))
		print_error();
}

#include "stdio.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
		print_error();
	arg_check(argv);
	init_philo(&rules ,argv);
	
}