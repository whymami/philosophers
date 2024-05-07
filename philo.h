#ifndef PHILPO_H
#define PHILPO_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_philo
{
	int			id;
	int 		x_eat;
	int			left_fork;
	int			right_fork;
	long long	last_eat;
	struct s_rules	*rules;
	pthread_t		thread;
}				t_philo;

typedef struct s_rules
{
    int            philo_count;
    int            time_to_die;
    int            time_to_eat;
    int            time_to_sleep;
    int            must_eat_count;
	pthread_mutex_t	forks[250];
	t_philo		*philo;
}				t_rules;

#endif