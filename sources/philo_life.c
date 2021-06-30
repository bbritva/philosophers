// #include "philo_one.h"
#include "../includes/philo_one.h"

int get_forks(t_data *params, int i)
{
    (void) params;
    printf("Philo #%d: get forks\n", i);
    return (0);
}

int put_forks(t_data *params, int i)
{
    (void) params;
    printf("Philo #%d: get forks\n", i);
    return (0);
}



void	*born_philo(void *data)
{
	t_data  *params;
	int     my_index;
	time_t	last_eat_time;
	
	params = (t_data *)data;
	pthread_mutex_lock(&params->mutex);
    my_index = ++params->index;
    pthread_mutex_unlock(&params->mutex);
	time(&params->last_eat_time[my_index - 1]);
	params->flag = IS_ALIVE;
    printf("Philo #%d: i'm alive\n", my_index);
    while (params->flag & IS_ALIVE)
    {
        get_forks(params, my_index);
        usleep(params->eat_time);
		time(&params->last_eat_time[my_index - 1]);
		put_forks(params, my_index);
        usleep(params->sleep_time);
    }
}