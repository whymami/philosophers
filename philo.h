/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:26:22 by muguveli          #+#    #+#             */
/*   Updated: 2024/06/01 16:13:33 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INVALID_ARGS_ERR "Invalid arguments"
# define THREAD_CREATE_ERR "Failed to create a thread"
# define THREAD_JOIN_ERR "Failed to join a thread"
# define MALLOC_ERR "malloc() failed to allocate memory"
# define MUTEX_INIT_ERR "Failed to initialize mutex"
# define MAX_MIN_INT "Integer overflow"

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

typedef struct s_data
{
	int		philo_count; //argv[1]
	int		philo_live_time; //argv[2]
	int		philo_eat_time; //argv[3]
	int		philo_sleep_time; //argv[4]
	int		philo_must_eat; //argv[5]
	int		philo_dead;
	pthread_mutex_t	display;
}			t_data;

typedef struct s_philo
{
	int	philo_index;
	int philo_loop;
	long long philo_start;
	long long philo_last_eat;
	pthread_mutex_t *left_fork; //sol çatal
	pthread_mutex_t *right_fork; //sağ çatal
	pthread_mutex_t philo_last_eat_mutex;
	pthread_t	philo_thread;
	t_data	*data; //argümanalara ulaşması için
}		t_philo;

int	ft_isdigit(int c);
long long	get_time(void);
long	ft_atol(const char *str);
void	ft_usleep(int wait_time);

#endif