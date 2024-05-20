#include "philo.h"

long long get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void display_status(t_philo *philo, char *status)
{
    long long time;

    pthread_mutex_lock(&philo->data->display_mutex);
    time = get_time() - philo->start_time;
    printf("%lld %d %s\n", time, philo->id, status);
    pthread_mutex_unlock(&philo->data->display_mutex);
}

int arg_control(int argc, char **argv)
{
    int i, j;

    if ((argc < 5 || argc > 6) && printf("%s\n", INVALID_ARGS_ERR))
        return 1;
    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (!ft_isdigit(argv[i][j]) && printf("%s\n", INVALID_ARGS_ERR))
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}
