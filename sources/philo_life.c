// #include "philo_one.h"
#include "../includes/philo_one.h"

int get_forks(t_data *params, int i)
{
    printf("Philo #%d: GET forks, alive = %d\n", i, params->flag);
    return (0);
}

int put_forks(t_data *params, int i)
{
	printf("Philo #%d: PUT forks, alive = %d\n", i, params->flag);
    return (0);
}



void	*philos_life(void *data)
{
	t_data  		*params;
	int     		my_index;

	params = (t_data *)data;
	pthread_mutex_lock(&params->mutex);
    my_index = params->index++;
	pthread_mutex_unlock(&params->mutex);
	gettimeofday(&params->philos[my_index].last_eat_time, NULL);
	printf("Philo #%d: i'm alive\n", my_index);
	params->philos[my_index].is_started = 1;
	if (params->limit_to_eat)
		params->philos[my_index].eat_count = params->limit_to_eat;
	while ((params->flag & IS_ALIVE) && (!params->limit_to_eat || \
		params->philos[my_index].eat_count))
    {
        get_forks(params, my_index);
        usleep(params->eat_time * KOEF);
		gettimeofday(&params->philos[my_index].last_eat_time, NULL);
		params->philos[my_index].eat_count--;
		put_forks(params, my_index);
        usleep(params->sleep_time * KOEF);
    }
	return (NULL);
}