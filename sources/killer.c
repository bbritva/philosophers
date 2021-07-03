#include "philo_one.h"

long delta_time(struct timeval last_eat_time)
{
	struct timeval curr_time;

	gettimeofday(&curr_time, 0);
	return ((curr_time.tv_sec - last_eat_time.tv_sec) * 1000 +
		(curr_time.tv_usec - last_eat_time.tv_usec) / 1000);
}

void	*kill_somebody(void *data)
{
	t_data	*params;
	int		i;
	long 	delta;

	if (data)
	{
		params = (t_data *)data;
		i = 0;
		while(params->flag & IS_ALIVE)
		{
			while (i < params->philos_count)
			{
				delta = delta_time(params->philos[i].last_eat_time);
				if (delta > params->death_time && params->philos[i].is_started)
				{
					params->flag = params->flag & ~(IS_ALIVE);
					printf("Philo #%d has been shot\n delta = %ld\n", i, delta);
//					pthread_mutex_lock(&params->mutex);
//					params->flag = params->flag & ~(IS_ALIVE);
//					pthread_mutex_unlock(&params->mutex);
					break ;
				}
				i++;
			}
			if (!(params->flag & IS_ALIVE))
				break ;
		}
	}
	return (0);
}
