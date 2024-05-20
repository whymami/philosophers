#include "philo.h"

static int start_simulation(t_philo *philo, t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philo)
    {
        philo[i].start_time = get_time();
        if (pthread_create(&philo[i].thread_id, NULL, live, &philo[i])
            && printf("%s\n", THREAD_CREATE_ERR))
            return 1;
        i++;
    }
    i = 0;
    while (i < data->num_of_philo)
    {
        if (pthread_join(philo[i].thread_id, NULL) && printf("%s\n", THREAD_JOIN_ERR))
            return 1;
        i++;
    }
    return 0;
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (arg_control(argc, argv) || init_data(&data, argv))
		return (1);
	forks = init_forks(&data);
	if (!forks)
		return (1);
	philo = init_philo(&data, forks);
	if (!philo)
		return (1);
	if (!start_simulation(philo, &data))
		return (1);
}
