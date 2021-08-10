#include "philo_main.h"

void	*death(t_philo *philo)
{
	long	delta;

//	pthread_mutex_lock(&philo->params->death_mutex);
	pthread_mutex_lock(&philo->params->print_mutex);
	delta = delta_time(philo->params->start_time);
	printf("%-8ld: Philo #%2d %s\n", delta, philo->index + 1, DEAD);
	return (0);
}

void	*full(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->death_mutex);
	pthread_mutex_lock(&philo->params->print_mutex);
	printf("%-8ld:%s", delta_time(philo->params->start_time), ALL_FULL);
	return (0);
}

void	*killer(void *data)
{
	t_philo		**philos;
	int			i;
	long		delta;
	long		death_time;

	if (!data)
		return (0);
	philos = (t_philo **)data;
	death_time = philos[0]->params->death_time;
	delay((int)death_time * 2 / 3);
	while (1)
	{
		i = -1;
		while (++i < philos[0]->params->philos_cnt)
		{
			if (philos[0]->params->full_cnt == philos[0]->params->philos_cnt)
				return (full(philos[i]));
			delta = delta_time(philos[i]->last_eat_time);
			pthread_mutex_lock(&(philos[0]->params->death_mutex));
			if (philos[i]->flag & STARTED && \
				delta > death_time)
				return (death(philos[i]));
			pthread_mutex_unlock(&(philos[0]->params->death_mutex));
		}
	}
}
