#include "philo_main.h"

void	*death(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->death_mutex);
	put_message(philo, DEAD);
	pthread_mutex_lock(&philo->params->mutex);
	return (0);
}

void	*full(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->death_mutex);
	pthread_mutex_lock(&philo->params->mutex);
	printf("%-8ld:%s", delta_time(philo->params->start_time), ALL_FULL);
	return (0);
}

void	*killer(void *data)
{
	t_philo		**philos;
	int			i;

	if (!data)
		return (0);
	philos = (t_philo **)data;
	while (1)
	{
		i = -1;
		while (++i < philos[0]->params->philos_cnt)
		{
			if (philos[i]->flag & STARTED && delta_time
				(philos[i]->last_eat_time) > philos[i]->params->death_time + 5)
				return (death(philos[i]));
			if (philos[0]->params->full_cnt == philos[0]->params->philos_cnt)
				return (full(philos[i]));
		}
	}
}
