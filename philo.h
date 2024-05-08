#ifndef PHILPO_H
#define PHILPO_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/time.h"


# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_data
{
	int				nb_of_philo;
	int				nb_of_circle;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	long			creation_time;
	pthread_mutex_t	*display;
}	t_data;

typedef struct s_philo
{
	int				index;
	int				loop;
	long			last_meal;
	pthread_t		id;
	pthread_mutex_t	*last_meal_x;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*circle_x;
	t_data			*data;
}	t_philo;

#endif