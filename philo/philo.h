/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:26:22 by muguveli          #+#    #+#             */
/*   Updated: 2024/06/01 20:59:22 by muguveli         ###   ########.fr       */
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
	int				philo_live_time;
	int				philo_eat_time;
	int				philo_sleep_time;
	int				philo_must_eat;
	int				philo_dead;
	pthread_mutex_t	display;
}					t_data;

typedef struct s_philo
{
	int				philo_index;
	int				philo_loop;
	long long		philo_start;
	long long		philo_last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_last_eat_mutex;
	pthread_t		philo_thread;
	t_data			*data;
}					t_philo;

int					init_data(t_data *data, char **argv);
int					arg_control(int argc, char **argv);
pthread_mutex_t		*init_forks(t_data *data);
t_philo				*init_philo(t_data *data, pthread_mutex_t *forks);
int					start_simulation(t_data *data, t_philo *philo);
void				display(t_philo *philo, char *msg);
void				ft_usleep(int wait_time);
long long			get_time(void);
int					ft_isdigit(int c);
long				ft_atol(const char *str);
void				destroy(t_data *data, pthread_mutex_t *forks,
						t_philo *philos);

#endif