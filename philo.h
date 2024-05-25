/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:26:22 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/25 17:53:23 by muguveli         ###   ########.fr       */
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
	int				philo_count;
	int				live_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	long			start_time;
	pthread_mutex_t	*display;
}					t_data;

typedef struct s_philo
{
	int				philo_idx;
	int				loop_count;
	long			last_eat;
	pthread_t		thread_id;
	pthread_mutex_t	*last_eat_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*loop_count_mutex;
	t_data			*data;
}					t_philo;

long				ft_atol(const char *str);
int					ft_isdigit(int c);
long long			get_time(void);
void				display(t_philo *philo, char *msg);
pthread_mutex_t		*init_mutex(char **argv);
t_philo				*init_philo(char **argv, int argc, pthread_mutex_t *forks);
int					init_thread(t_philo *philo);
void				eat(t_philo *philo);
int					stalker(t_philo *philo);
void				ft_usleep(int time);

#endif