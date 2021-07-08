#include "philo_main.h"

void	*killer(void *data)
{
	t_philo		**philos;
	int 		i;

	if(!data)
		return (0);
	philos = (t_philo **)data;
	while (1)
	{
		i = -1;
		while (++i < philos[0]->params->philos_count)
		{
			if (philos[i]->flag & IS_STARTED && \
            delta_time(philos[i]->last_eat_time) >
			philos[i]->params->death_time)
			{
				pthread_mutex_lock(&philos[i]->params->death_mutex);
				put_message(philos[i], DEAD);
				return (0);
			}
			if (philos[0]->params->full_count == philos[0]->params->philos_count)
			{
				pthread_mutex_lock(&philos[i]->params->death_mutex);
				printf(ALL_FULL);
				return (0);
			}
		}
	}
}

