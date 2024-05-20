#include "philo.h"

pthread_mutex_t *init_forks(t_data *data)
{
    pthread_mutex_t *forks;
    int i;

    forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
    if (!forks && printf("%s\n", MALLOC_ERR))
        return NULL;
    i = 0;
    while (i < data->num_of_philo)
    {
        if (pthread_mutex_init(&forks[i], NULL) && printf("%s\n", MUTEX_INIT_ERR))
            return NULL;
        i++;
    }
    return forks;
}

t_philo *init_philo(t_data *data, pthread_mutex_t *fork_arr)
{
    t_philo *philo;
    int i;

    philo = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
    if (!philo && printf("%s\n", MALLOC_ERR))
        return NULL;
    i = 0;
    while (i < data->num_of_philo)
    {
        philo[i].id = i + 1;
        philo[i].nbr_of_meals = 0;
        philo[i].left_fork = &fork_arr[i];
        philo[i].right_fork = &fork_arr[(i + 1) % data->num_of_philo];
        philo[i].last_meal_time = get_time();
        philo[i].data = data;
        i++;
    }
    return philo;
}

int init_data(t_data *data, char **argv)
{
    data->num_of_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->is_dead = 0;
    if (argv[5])
        data->num_of_must_eat = ft_atoi(argv[5]);
    else
        data->num_of_must_eat = -1;
    if (pthread_mutex_init(&data->display_mutex, NULL) && printf("%s\n", MUTEX_INIT_ERR))
        return 1;
    return 0;
}
