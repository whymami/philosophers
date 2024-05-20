#include "philo.h"


void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        display_status(philo, FORK);
        pthread_mutex_lock(philo->left_fork);
        display_status(philo, FORK);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        display_status(philo, FORK);
        pthread_mutex_lock(philo->right_fork);
        display_status(philo, FORK);
    }
    display_status(philo, EATING);
    philo->nbr_of_meals++;
    philo->last_meal_time = get_time();
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    display_status(philo, SLEEPING);
    usleep(philo->data->time_to_sleep * 1000);
    display_status(philo, THINKING);
}

void *live(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!philo->data->is_dead)
    {
        if (philo->data->num_of_must_eat != -1 && philo->nbr_of_meals >= philo->data->num_of_must_eat)
            break;
        take_forks(philo);
        if (get_time() - philo->last_meal_time >= philo->data->time_to_die)
        {
            display_status(philo, DEAD);
            philo->data->is_dead = 1;
            break;
        }
    }
    return NULL;
}
