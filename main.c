/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:31:40 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/25 17:04:15 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	long	start;
	long	end;

	start = get_time();
	end = get_time();
	while (end - start < time)
	{
		usleep(100);
		end = get_time();
	}
}

static int	arg_control(int argc, char **argv)
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

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (arg_control(argc, argv))
		return (1);
	forks = init_mutex(argv);
	if (!forks)
		return (1);
	philo = init_philo(argv, argc, forks);
	if (!philo)
		return (1);
	if (!init_thread(philo))
		return (1);
	if (stalker(philo))
		return (1);
}
