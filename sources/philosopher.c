#include "philo_main.h"

long delta_time(struct timeval last_eat_time)
{
	struct timeval curr_time;

	gettimeofday(&curr_time, 0);
	return ((curr_time.tv_sec - last_eat_time.tv_sec) * 1000 +
		(curr_time.tv_usec - last_eat_time.tv_usec) / 1000);
}

void	*philosopher(void *data)
{
	pthread_t	lifecycle;
	long 		delta;
	t_philo  	*me;

	if (!data)
		return (0);
	me = (t_philo *)data;
	gettimeofday(&me->last_eat_time, NULL);
	printf("Philo #%d: i'm alive\n", me->index);
	pthread_create(&lifecycle, NULL, philos_lifecycle, (void *)me);
	while(1)
	{
		delta = delta_time(me->last_eat_time);
		if (delta > me->params->death_time)
		{
			me->params->flag = me->params->flag & ~(IS_ALIVE);
			pthread_detach(lifecycle);
			printf("Philo #%d killed\n delta = %ld\n", me->index, delta);
			break ;
		}
	}
	return (0);
}
