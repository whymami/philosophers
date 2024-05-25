/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:33:41 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/25 16:04:13 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_error(char *msg)
		// daha detaylı hale getirilecek freeleme vs eklenecek unutma aq
{
	printf("%s\n", msg);
	exit(1);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == 43 || str[i] == 45))
		if (str[i++] == 45)
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57)
		tmp = (tmp * 10) + (str[i++] - 48);
	if (tmp * sign < -2147483648 || tmp * sign > 2147483647)
		display_error(MAX_MIN_INT);
	return (tmp * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	display(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->data->display);
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->philo_idx, msg);
	pthread_mutex_unlock(philo->data->display);
}
