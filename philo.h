/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleynakoluk <aleynakoluk@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:59:41 by muguveli          #+#    #+#             */
/*   Updated: 2024/05/20 22:52:37 by aleynakoluk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include "libft/libft.h"

# define INVALID_ARGS_ERR "Invalid arguments"
# define THREAD_CREATE_ERR "Failed to create a thread"
# define THREAD_JOIN_ERR "Failed to join a thread"
# define MALLOC_ERR "malloc() failed to allocate memory"
# define MUTEX_INIT_ERR "Failed to initialize mutex"

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"


//alınana argümanların tutulduğu struct
typedef struct s_data 
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				is_dead;
	pthread_mutex_t	display_mutex;
} 					t_data;

//philo bilgilerinin tutulduğu struct
typedef struct s_philo
{
	int				id;
	int				nbr_of_meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal_time;
	pthread_t		thread_id;
	long long		start_time;
	t_data			*data;
}					t_philo;

long long get_time(void);
pthread_mutex_t *init_forks(t_data *data);
t_philo *init_philo(t_data *data, pthread_mutex_t *fork_arr);
int arg_control(int argc, char **argv);
int init_data(t_data *data, char **argv);
void display_status(t_philo *philo, char *status);
void take_forks(t_philo *philo);
void *live(void *arg);

#endif